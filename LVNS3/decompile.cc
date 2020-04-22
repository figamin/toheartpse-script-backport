#include <stdio.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "fonttable.h"
#include "opcodes.h"

int main(int argc, char** argv) {
  FILE* inp = fopen(argv[1], "rb");
  uint8_t readbuf[12];
  std::unordered_map<uint16_t, std::vector<uint16_t> > lbls;

  fread(readbuf, 2, 1, inp);
  uint16_t num_blk = readbuf[1] << 8 | readbuf[0];

  for (uint16_t i = 0; i < num_blk; i++) {
    fread(readbuf, 2, 1, inp);
    uint16_t offset = readbuf[1] << 8 | readbuf[0];
    lbls[offset].push_back(i);
  }

  if (std::string(argv[1]).find(".DATA") != std::string::npos) {
    // TODO: read and check file size
    fseek(inp, 2, SEEK_CUR);
  }

  bool intext = false;
  while (fread(readbuf, 1, 1, inp) != 0) {
    if (lbls.find(ftell(inp) - 1) != lbls.end()) {
      if (intext) {
        printf("\"\n");
        intext = false;
      }

      for (const auto& lbl : lbls[ftell(inp) - 1]) {
        if (lbl != 0) {
          printf("\n");
        }
        printf("*%02x\n", lbl);
      }
    }

    if (readbuf[0] >= 0 && readbuf[0] < 0x20) {
      if (!intext) {
        printf("Text \"");
        intext = true;
      }
      fread(readbuf + 1, 1, 1, inp);
      uint16_t n = readbuf[0] << 8 | readbuf[1];
      if (n < fonttable.size()) {
        std::cout << fonttable[n];
      }
    } else {
      if (intext) {
        printf("\"\n");
        intext = false;
      }

      if (opcodes.find(readbuf[0]) == opcodes.end()) {
        printf("UnknownOpcode %02x\n", readbuf[0]);
      } else {
        auto op = opcodes[readbuf[0]];
        std::cout << std::get<0>(op);
        auto arglen = std::get<1>(op);

        switch (readbuf[0]) {
          case 0x21:
            fread(readbuf, 1, 1, inp);
            printf(" %02x", readbuf[0]);
            if (readbuf[0] == 0x03) {
              arglen = 0;
            } else {
              arglen = 4;
            }
            break;
          case 0x24:
            fread(readbuf, 1, 1, inp);
            printf(" %02x", readbuf[0]);
            fread(readbuf, 1, 1, inp);
            printf(" %02x", readbuf[0]);
            arglen = 2 * readbuf[0];
            break;
          case 0x2b:
            while (true) {
              uint8_t lastc = readbuf[0];
              fread(readbuf, 1, 1, inp);
              if (lastc == 0x20 && readbuf[0] == 0x20) {
                printf("\nEnd20\n");
                break;
              }
              printf(" %02x", readbuf[0]);
            }
            continue;
            break;
        }

        for (uint16_t i = 0; i < arglen; i++) {
          fread(readbuf, 1, 1, inp);
          printf(" %02x", readbuf[0]);
        }

        printf("\n");
      }
    }
  }

  return 0;
}
