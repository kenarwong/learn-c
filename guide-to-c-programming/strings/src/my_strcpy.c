#include <stdio.h>

char strA[80] = "A string to be used for demonstration purposes";
char strB[80] = "12345678901234567890123456789012345678901234567890";

char *my_strcpy(char *destination, const char *source)
{
  char *p = destination;
  //while (*source != '\0')
  while (*source) // will go to 0
  {
    *p++ = *source++;
  }
  *p = '\0';
  return destination;
}

int main(void)
{
  my_strcpy(strB, strA);
  puts(strB);
}