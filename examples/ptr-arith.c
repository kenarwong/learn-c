#include <stdio.h>

typedef unsigned long uint64;

void foo(void *ptr)
{
  printf("ptr: %p\n", ptr);

  // not safe to do pointer arithmetic on void *
  // does not compile with -pedantic
  // void *pos = ptr + 10; // doesn’t compile!
  // printf("ptr: %p\n", pos);

  void *pos = (char *)ptr + 10; // works fine
  printf("ptr: %p\n", pos);

  uint64 addr = (uint64)pos; // can convert to int
  addr += 10;
  printf("addr: %lx\n", addr);

  pos = (void *)addr; // and back again
  printf("ptr: %p\n", pos);
}

int
main(int ac, char **av)
{
  foo((void *)0x1234567890);

  int x[5];
  printf("%p\n", (void*)x);
  printf("%p\n", (void*)(x+1)); //equivalent to &x[0] + 1
  printf("%p\n", (void*)&x);
  printf("%p\n", (void*)(&x+1)); // eqv. to x + sizeof(x[5])

  return 0;
}
