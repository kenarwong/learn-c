#include <stdio.h>

int main(void)
{
  char multi[5][10] = {
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'},
    {'9', '8', '7', '6', '5', '4', '3', '2', '1', '0'},
    {'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'},
  };

  printf("%c\n", multi[0][3]);  
  printf("%c\n", multi[1][7]);  
  printf("%c\n", multi[4][0]);  
  printf("%c\n", *(*(multi + 3) + 1));  // 8
}