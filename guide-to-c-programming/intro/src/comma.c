#include <stdio.h>

int main(void) {
  int i, j;
  for (i = 0, j = 10; i < 100; i++, j++)
    printf("%d, %d\n", i, j);
}
