#!/usr/bin/python3

import argparse
import png
import n64img.image
from typing import List, Tuple


def generate_grey_palette() -> List[Tuple[int, int, int, int]]:
    def generate_grey_color(intensity: int) -> Tuple[int, int, int, int]:
        return intensity, intensity, intensity, 255

    return [
        generate_grey_color(0x00),
        generate_grey_color(0x11),
        generate_grey_color(0x22),
        generate_grey_color(0x33),
        generate_grey_color(0x44),
        generate_grey_color(0x55),
        generate_grey_color(0x66),
        generate_grey_color(0x77),
        generate_grey_color(0x88),
        generate_grey_color(0x99),
        generate_grey_color(0xAA),
        generate_grey_color(0xBB),
        generate_grey_color(0xCC),
        generate_grey_color(0xDD),
        generate_grey_color(0xEE),
    ]


def get_encoded_image(file_name: str) -> bytearray:
    img = png.Reader(file_name).read()
    width = img[0]
    height = img[1]
    rows = img[2]
    info = img[3]
    palette = info["palette"]
    if width != 256:
        return f"'{file_name}' width must be 256 but found {width} instead"
    if height != 128:
        return f"'{file_name}' height must be 128 but found {height} instead"
    if info["planes"] != 1 or info["bitdepth"] != 8:
        return f"'{file_name}' must be an indexed image"
    if len(palette) != 16:
        return f"'{file_name}' palette must be of 16 colors but found {len(palette)} colors instead"

    data = bytearray((width * height) >> 1)
    idx = 0
    nibble = False
    for row in rows:
        for ch in row:
            if nibble == False:
                nibble = True
                data[idx] = ch
            else:
                nibble = False
                data[idx] |= ch << 4
                idx += 1
    return data


def encode(input, output):
    data = get_encoded_image(input)
    with open(output, "wb") as f_out:
        f_out.write(data)


def decode_image(data: bytes, output: str, w: int, h: int, bpp: int):
    if bpp == 4:
        img = n64img.image.CI4(data, w, h)
    elif bpp == 8:
        img = n64img.image.CI8(data, w, h)
    else:
        raise f"bpp '{bpp}' invalid"
    img.little_endian = True
    img.palette = generate_grey_palette()
    img.write(output)


def decode(input: str, output: str, w: int, h: int, bpp: int):
    with open(input, "rb") as f_out:
        raw_data = f_out.read()
    img_size = int(w * h * bpp / 8)
    img_count = int(len(raw_data) / img_size)
    print(f"img_size: {img_size}")
    print(f"img_count: {img_count}")
    if img_count == 1:
        decode_image(raw_data, output, w, h, bpp)
    else:
        image_base_name = output.replace(".png", "").replace(".PNG", "")
        in_data = raw_data
        for i in range(0, img_count):
            name = f"{image_base_name}_{i}.png"
            decode_image(in_data[:img_size], name, w, h, bpp)
            in_data = in_data[img_size:]


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="convert images between PNG and BIN")
    subparsers = parser.add_subparsers(dest="command")

    encode_parser = subparsers.add_parser(
        "encode",
        description="Encode a PNG file into BIN",
    )
    encode_parser.add_argument("input")
    encode_parser.add_argument("output")

    decode_parser = subparsers.add_parser(
        "decode",
        description="Encode a BIN file into PNG",
    )
    decode_parser.add_argument("input")
    decode_parser.add_argument("output")
    decode_parser.add_argument(
        "--bpp", "-b", type=int, help="Bits per pixel: 4 = 4bpp (default), 8 = 8bpp"
    )
    decode_parser.add_argument("--width", type=int, help="Image width (default: 128)")
    decode_parser.add_argument("--height", type=int, help="Image height (default: 128)")

    args = parser.parse_args()
    if args.command == "encode":
        encode(args.input, args.output)
    elif args.command == "decode":
        if not args.bpp:
            args.bpp = 4
        if not args.width:
            args.width = 128
        if not args.height:
            args.height = 128
        decode(args.input, args.output, args.width, args.height, args.bpp)
    else:
        parser.print_help()
