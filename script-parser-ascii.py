import sys

# fmt: off
LEADERS = (
    b"\x81", b"\x82", b"\x83", b"\x84", b"\x87", b"\x88", b"\x89", b"\x8A",
    b"\x8B", b"\x8C", b"\x8D", b"\x8E", b"\x8F", b"\x90", b"\x91", b"\x92",
    b"\x93", b"\x94", b"\x95", b"\x96", b"\x97", b"\x98", b"\x99", b"\x9A",
    b"\x9B", b"\x9C", b"\x9D", b"\x9E", b"\x9F", b"\xE0", b"\xE1", b"\xE2",
    b"\xE3", b"\xE4", b"\xE5", b"\xE6", b"\xE7", b"\xE8", b"\xE9", b"\xEA",
    b"\xED", b"\xEE", b"\xF0", b"\xF1", b"\xF2", b"\xF3", b"\xF4", b"\xF5",
    b"\xF6", b"\xF7", b"\xF8", b"\xF9", b"\xFA", b"\xFB", b"\xFC"
)
# fmt: on


def bidx(b, idx):
    return b[idx : idx + 1]


def main(f):
    with open(f, "rb") as infile:
        contents = infile.read()

    i = 0
    while i < len(contents):
        b = bidx(contents, i)

        if b in LEADERS and i > 0:
            # Double-byte Shift-JIS (little-endian: [trail][lead])
            sys.stdout.buffer.write(bidx(contents, i))  # trail
            sys.stdout.buffer.write(bidx(contents, i - 1))                     # lead
            i += 1  # skip the leader (the previous byte was already handled)
        else:
            # ASCII or other single-byte data
            sys.stdout.buffer.write(b)
        i += 1


if __name__ == "__main__":
    main(sys.argv[1])
