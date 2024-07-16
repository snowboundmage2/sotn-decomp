package main

import "io"

func decompressData(r io.Reader) (dst []byte) {
	writeNibbleFlag := 0
	writeNibble := func(ch byte) {
		if writeNibbleFlag == 0 {
			writeNibbleFlag = 1
			dst = append(dst, ch)
		} else {
			writeNibbleFlag = 0
			dst[len(dst)-1] += ch * 16
		}
	}
	srcCh := make([]byte, 1)
	readNibbleFlag := 0
	readNibble := func() (ch byte) {
		if readNibbleFlag != 0 {
			readNibbleFlag = 0
			ch = srcCh[0]
			return ch & 0xF
		} else {
			readNibbleFlag = 1
			_, _ = r.Read(srcCh)
			ch = srcCh[0]
			return (ch >> 4) & 0xF
		}
	}

	buf := make([]byte, 8)
	_, _ = r.Read(buf)
	for {
		op := int(readNibble())
		switch op {
		case 0:
			length := int(readNibble())
			op = int(readNibble())
			for i := 0; i < length*0x10+op+0x13; i++ {
				writeNibble(0)
			}
		case 2:
			ch := readNibble()
			writeNibble(ch)
			writeNibble(ch)
		case 4:
			writeNibble(readNibble())
			fallthrough
		case 3:
			writeNibble(readNibble())
			fallthrough
		case 1:
			writeNibble(readNibble())
		case 5:
			ch := readNibble()
			length := int(readNibble())
			for i := 0; i < length+3; i++ {
				writeNibble(ch)
			}
		case 6:
			length := int(readNibble())
			for i := 0; i < length+3; i++ {
				writeNibble(0)
			}
		case 7, 8, 9, 10, 11, 12, 13, 14:
			length := int(buf[op-7])
			switch length & 0xF0 {
			case 0x20:
				writeNibble(byte(length & 0xF))
				fallthrough
			case 0x10:
				writeNibble(byte(length & 0xF))
			case 0x60:
				for i := 0; i < (length&0xF)+3; i++ {
					writeNibble(0)
				}
			}
		case 15:
			return dst
		}
	}

	return []byte{}
}
