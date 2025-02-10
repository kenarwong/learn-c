#include <stdio.h>

int main(void) {
  // int a;
  // int b;
  int a, b;  // Same thing


  // int c;
  // int *d;
  int c, *d;  // Same thing

  // int *p;
  // int q;
  int *p, q;  // p is a pointer to an int; q is just an int.

  // Prints size of an int
  printf("%zu\n", sizeof(int));

  // p is type 'int *', so prints size of 'int*' (pointer to int)
  printf("%zu\n", sizeof p);

  // *p is type 'int', so prints size of 'int'
  printf("%zu\n", sizeof *p);
}