package main

import (
	"encoding/binary"
	"fmt"
	"io"
	"os"
)

type gfxKind uint16

const (
	gfxBankNone = gfxKind(iota)
	gfxBank4bpp
	gfxBank8bpp
	gfxBank16bpp
	gfxBankCompressed
)

type gfxEntryPrivate struct {
	X      uint16
	Y      uint16
	Width  uint16
	Height uint16
	Data   PsxOffset
}
type gfxBlockPrivate struct {
	kind    gfxKind
	flags   uint16
	entries []gfxEntryPrivate
}

type gfxEntry struct {
	dataRange
	X        uint16 `json:"x"`
	Y        uint16 `json:"y"`
	Width    uint16 `json:"width"`
	Height   uint16 `json:"height"`
	Filename string `json:"filename,omitempty"`
	data     []byte
}
type gfxBlock struct {
	Kind    gfxKind    `json:"Kind"`
	Flags   uint16     `json:"Flags"`
	Entries []gfxEntry `json:"Entries"`
}
type gfx struct {
	Blocks  []gfxBlock `json:"Blocks"`
	Indices []int      `json:"Indices"`
}

func readGraphicsEntry(f *os.File, kind gfxKind, entry gfxEntryPrivate) (gfxEntry, error) {
	fileName := fmt.Sprintf("gfx_%s", entry.Data.String()[2:])
	switch kind {
	case gfxBankNone:
		if entry.Data != RamNull {
			return gfxEntry{}, fmt.Errorf("a None Kind should contain a NULL ptr, but I found %v", entry.Data)
		}
		return gfxEntry{
			X:      entry.X,
			Y:      entry.Y,
			Width:  entry.Width,
			Height: entry.Height,
			data:   nil,
		}, nil
	case gfxBank4bpp:
		return gfxEntry{}, fmt.Errorf("graphics of Kind 4bpp is not yet supported (%v)", entry.Data)
	case gfxBank8bpp:
		return gfxEntry{}, fmt.Errorf("graphics of Kind 8bpp is not yet supported (%v)", entry.Data)
	case gfxBank16bpp:
		return gfxEntry{}, fmt.Errorf("graphics of Kind 16bpp is not yet supported (%v)", entry.Data)
	case gfxBankCompressed:
		if err := entry.Data.moveFile(f); err != nil {
			return gfxEntry{}, fmt.Errorf("unable to read graphics entry: %v", err)
		}
		// the only way to know the size of the compressed data is to decompress it and see how many bytes were read
		start, _ := f.Seek(0, io.SeekCurrent)
		_ = decompressData(f)
		now, _ := f.Seek(0, io.SeekCurrent)
		cmpData := make([]byte, int(now-start))
		if err := entry.Data.moveFile(f); err != nil {
			return gfxEntry{}, fmt.Errorf("unable to read graphics entry: %v", err)
		}
		f.Read(cmpData)

		return gfxEntry{
			dataRange: dataRange{
				begin: entry.Data,
				end:   entry.Data.sum(len(cmpData)).align4(),
			},
			X:        entry.X,
			Y:        entry.Y,
			Width:    entry.Width,
			Height:   entry.Height,
			Filename: fmt.Sprintf("%s.cmp.bin", fileName),
			data:     cmpData,
		}, nil
	default:
		return gfxEntry{}, fmt.Errorf("unrecognized graphics Kind %v (%v)", kind, entry.Data)
	}
}

func readGraphics(file *os.File, off PsxOffset) (gfx, []dataRange, error) {
	if err := off.moveFile(file); err != nil {
		return gfx{}, nil, err
	}

	blockOffsets := []PsxOffset{}
	for {
		var offBank PsxOffset
		if err := binary.Read(file, binary.LittleEndian, &offBank); err != nil {
			return gfx{}, nil, err
		}
		if offBank >= off {
			break
		}
		blockOffsets = append(blockOffsets, offBank)
	}

	// the order of each gfxBlockPrivate must be preserved
	pool := map[PsxOffset]int{}
	pool[RamNull] = -1
	blocks := []gfxBlockPrivate{}
	ranges := []dataRange{}
	for _, blockOffset := range sortUniqueOffsets(blockOffsets) {
		if blockOffset == RamNull { // exception for ST0 as pointers can be NULL
			continue
		}
		if err := blockOffset.moveFile(file); err != nil {
			return gfx{}, nil, err
		}
		var block gfxBlockPrivate
		if err := binary.Read(file, binary.LittleEndian, &block.kind); err != nil {
			return gfx{}, nil, err
		}
		if err := binary.Read(file, binary.LittleEndian, &block.flags); err != nil {
			return gfx{}, nil, err
		}

		if block.kind == gfxKind(0xFFFF) && block.flags == 0xFFFF { // exception for ST0 as Blocks can be empty
			pool[blockOffset] = len(blocks)
			blocks = append(blocks, block)
			ranges = append(ranges, dataRange{
				begin: blockOffset,
				end:   blockOffset.sum(4),
			})
			continue
		}

		for {
			var entry gfxEntryPrivate
			if err := binary.Read(file, binary.LittleEndian, &entry); err != nil {
				return gfx{}, nil, err
			}
			if entry.X == 0xFFFF && entry.Y == 0xFFFF {
				break
			}
			block.entries = append(block.entries, entry)
		}
		pool[blockOffset] = len(blocks)
		blocks = append(blocks, block)
		ranges = append(ranges, dataRange{
			begin: blockOffset,
			end:   blockOffset.sum(4 + len(block.entries)*12 + 4),
		})
	}

	var g gfx
	g.Blocks = make([]gfxBlock, len(blocks))
	for i, block := range blocks {
		g.Blocks[i] = gfxBlock{
			Kind:    block.kind,
			Flags:   block.flags,
			Entries: make([]gfxEntry, len(block.entries)),
		}
		for j, e := range block.entries {
			newEntry, err := readGraphicsEntry(file, block.kind, e)
			if err != nil {
				return gfx{}, nil, err
			}
			g.Blocks[i].Entries[j] = newEntry
		}
	}
	for _, blockOffset := range blockOffsets {
		g.Indices = append(g.Indices, pool[blockOffset])
	}

	headerRange := mergeDataRanges(append(ranges, dataRange{
		begin: off,
		end:   off.sum(len(blockOffsets) * 4),
	}))
	dataRanges := []dataRange{}
	for _, block := range g.Blocks {
		for _, entry := range block.Entries {
			if !entry.dataRange.empty() {
				dataRanges = append(dataRanges, entry.dataRange)
			}
		}
	}

	return g, []dataRange{headerRange, mergeDataRanges(dataRanges)}, nil
}
