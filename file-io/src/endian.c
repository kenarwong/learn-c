#include <stdio.h>

int main(void) {
  FILE* fp;

  fp = fopen("endian.bin", "wb");

  unsigned short v = 0x1234;  // Two bytes, 0x12 and 0x34

  fwrite(&v, sizeof v, 1, fp); // Write the two bytes to the file

  // Big endian (MSB first)
  // First byte: 0x12
  // Second byte: 0x34

  fclose(fp);
}