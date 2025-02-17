#include <stdio.h>

int main(void) {
  int i = 10;
  int j = 5 + i++;  // Compute 5 + i, _then_ increment i
  
  printf("%d, %d\n", i, j);  // Prints 11, 15

  i = 10;
  j = 5 + ++i;  // Increment i, _then_ compute 5 + i
  
  printf("%d, %d\n", i, j);  // Prints 11, 16
}
