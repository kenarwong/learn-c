#include <stdio.h>

typedef int Array1d[10];

int main() {

  Array1d arr; // pointer to 1-d array of 10 integers
  Array1d arr2d[5]; // 2d array, 5 1d arrays of 10 integers

  // pointer to 1d array, same as 2d array
  Array1d *ptr; 
  ptr = arr2d;

  // some pointer arithmetic
  printf("arr: %p, arr+1: %p\n", (void*)arr, (void*)(arr+1));

  printf("sizeof(Array1d): %zu (0x%x)\n", sizeof(Array1d), (unsigned)sizeof(Array1d));

  // constant 2d array pointer
  printf("sizeof(*arr2d): %zu (0x%x)\n", sizeof(*arr2d), (unsigned)sizeof(*arr2d));
  printf("sizeof(arr2d): %zu (0x%x)\n", sizeof(arr2d), (unsigned)sizeof(arr2d));
  printf("arr2d: %p, arr2d+1: %p\n", (void*)arr2d, (void*)(arr2d+1));

  // pointer to a 2d array pointer
  printf("sizeof(*ptr): %zu\n", sizeof(*ptr));
  printf("sizeof(ptr): %zu\n", sizeof(ptr));
  printf("ptr: %p, ptr+1: %p\n", (void*)ptr, (void*)(ptr+1));

  // Same thing as typedef
  int(*p1d)[10]; // pointer to 1d array of 10 integers
  // different from
  // int *p1d[10]; // this is an array of 10 pointers to integers

  // int*
  printf("sizeof(*p1d): %zu (0x%x)\n", sizeof(*p1d), (unsigned)sizeof(*p1d));
  printf("sizeof(p1d): %zu (0x%x)\n", sizeof(p1d), (unsigned)sizeof(p1d));

  return 0;
}

