#include <stdio.h>

struct a {
  int foo;
};
struct b {
  struct a bar;
  long baz;
};

int
main(int ac, char **av)
{
  printf("%ld\n", sizeof(struct b));

  return 0;
}
