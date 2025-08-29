#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  uint8_t c1, c2;

  c1 = getc(stdin);
  c2 = getc(stdin);
  uint16_t numblk = c2 << 8 | c1;

  c1 = getc(stdin);
  c2 = getc(stdin);
  uint16_t datalen = c2 << 8 | c1;

  uint16_t* blk = calloc(numblk, sizeof(uint16_t));
  int intext = 0;
  for (uint16_t i = 0; i < numblk; i++) {
    c1 = getc(stdin);
    c2 = getc(stdin);
    blk[i] = c2 << 8 | c1;
  }

  for (uint16_t i = 0; i < datalen; i++) {
    for (uint16_t j = 0; j < numblk; j++) {
      if (i == blk[j]) {
        printf("\n*%02x\n", j);
      }
    }
    c1 = getc(stdin);
    c2 = getc(stdin);
    if (c2 >= 0x81 && c2 <= 0xee) {
      if (!intext) {
        printf("Text \"");
        intext = 1;
      }
      putc(c2, stdout);
      putc(c1, stdout);
    } else {
      if (intext) {
        printf("\"\n");
        intext = 0;
      }
      if (c2 == 0x03 && c1 == 0xea) {
        printf("WaitKey\n");
      } else if (c2 == 0x03 && c1 == 0xec) {
        printf("WaitPage\n");
      } else {
        printf("Opcode %02x %02x\n", c2, c1);
      }
    }
  }

  free(blk);
  return 0;
}
