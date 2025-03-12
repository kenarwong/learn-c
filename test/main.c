#include <stdio.h>

extern int y;
extern int b(); // not necessary, but good practice 

int main() {
  // printf("%d",x);
  // printf("%d",a());

  printf("%d",b());
  printf("%d",y);

  return 0;
}
