#include <stdio.h>

char a[20];
int i;

int main(void)
{ 
  a[3] = 'x'; // (a + i)
  for (int i = 0; i < 5; i++)
    printf("%c", a[i]); 

  printf("\n");

  // oddity
  3[a] = 'y'; // (i + a)

  for (int i = 0; i < 5; i++)
    printf("%c", a[i]); 
  printf("\n");

  return 0;
}