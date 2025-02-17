#include <stdio.h>

// Note that this only works for arrays, not when you take pointers
void reverse_str(char *str)
{ 
  //wrong
  int strlength = (&str)[1] - str;
}

int main(void) {
  int arr[5] = {1, 2, 3, 4, 5};
  printf("Address of arr      is %p\n", (void*)arr);
  printf("Address of &arr     is %p\n", (void*)&arr);

  // type of arr is int[5], so arr + 1 is the address of the second element
  printf("Address of arr + 1  is %p\n", (void*)(arr + 1));

  // type of &arr is int(*)[5], so &arr + 1 is the address of the next array
  printf("Address of &arr + 1 is %p\n", (void*)(&arr + 1));
}