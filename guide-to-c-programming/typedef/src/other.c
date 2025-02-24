#include <stdio.h>

//typedef float app_float;
typedef long double app_float;
app_float f1, f2, f3;

typedef int *intptr;

// Make type five_ints an array of 5 ints
typedef int five_ints[5];

int main(void)
{
  int a = 10;
  intptr x = &a;  // "intptr" is type "int*"

  five_ints i = {11, 22, 33, 44, 55};

  return 0;
}