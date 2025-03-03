#include <stdio.h>
#include <stdlib.h>

int main()
{
  int *p = NULL;
  int length = 0;
  int i = 3;

  while (i--)
  {
    printf("pointer: %p, length: %d\n", (void *)p, length);
    
    // Allocate 10 more ints:
    length += 10;
    p = realloc(p, sizeof *p * length);

    // Do amazing things
    // ...
    
  }
}