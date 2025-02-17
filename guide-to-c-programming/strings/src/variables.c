#include <stdio.h>

int main(void)
{
  char *s = "Hello, World!";
  printf("%s\n", s);

  // char s[14] = "Hello, world!";

  // or, if we were properly lazy and have the compiler
  // figure the length for us:

  char t[] = "Hello, world!";
  for (int i = 0; i < 13; i++)
     printf("%c\n", t[i]);

  // If we try to modify a string literal, we get a segfault
  // s[0] = 'z';  // BAD NEWS: tried to mutate a string literal!

  // Character arrays are not string literals, so we can modify them
  t[0] = 'z'; //  No problem
  printf("%s\n", t);  // "zello, again!"

  // Pointer arrays allow for multiple character arrays
  char *pointerArray[]={"one","two","three"};
  printf("%s\n%s\n%s\n",pointerArray[0],pointerArray[1],pointerArray[2]);

  return 0;
}
