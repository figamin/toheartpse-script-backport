import sys

def to_fullwidth(text: str) -> str:
    result = []
    for ch in text:
        code = ord(ch)
        if ch == " ":
            result.append("　")
        elif 0x21 <= code <= 0x7E:
            result.append(chr(code + 0xFEE0))
        else:
            result.append(ch)
    return "".join(result)

def process_file(filename: str) -> str:
    with open(filename, "r", encoding="utf-8") as f:
        text = f.read()

    fullwidth = to_fullwidth(text)

    encoded = fullwidth.encode("shift_jis", errors="strict")

    hex_pairs = []
    for b in encoded:
        hex_pairs.append(f"{b:02X}")

    reversed_pairs = []
    for i in range(0, len(hex_pairs), 2):
        if i + 1 < len(hex_pairs):
            reversed_pairs.append(hex_pairs[i+1] + hex_pairs[i])
        else:
            reversed_pairs.append(hex_pairs[i])

    return "".join(reversed_pairs)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 script.py input.txt")
        sys.exit(1)

    filename = sys.argv[1]
    output = process_file(filename)
    print(output)
