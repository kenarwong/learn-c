#include <stdio.h>

int main(void) {
  int *p;

  p = NULL;

  printf("p is %p\n", (void*)p);  // prints "nil"

  // Dereferencing a NULL pointer will crash the program
  // *p = 12; // this will crash the program
}