#include <stdio.h>

int main(void) {
  int x = 13;
  int y = 13;
  y += x > 10? 17: 37;
  printf("y = %d\n", y);
}
