#include <stdio.h>

int main(void)
{
  typedef int antelope;  // Make "antelope" an alias for "int"
  
  antelope x = 10;       // Type "antelope" is the same as type "int"
  
  typedef int antelope, bagel, mushroom;  // These are all "int"

  return 0;
}