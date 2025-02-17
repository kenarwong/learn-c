#include <stdio.h>

int main(void)
{
  int goat_count = 2;

  switch (goat_count)
  {
  case 0:
    printf("You have no goats.\n");
    break;

  case 1:
    printf("You have a singular goat.\n");
    break;

  case 2:
    printf("You have a brace of goats.\n");
    break;

  default:
    printf("You have a bona fide plethora of goats!\n");
    break;
  }

  // Fall through example
  int x = 1;
  switch (x)
  {
  case 1:
    printf("1\n");
    // Fall through!
  case 2:
    printf("2\n");
    break;
  case 3:
    printf("3\n");
    break;
  }
}