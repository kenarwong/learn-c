#include <stdio.h>

// often globally available
struct car {
    char *name;
    float price;
    int speed;
};

int main(void)
{
  struct car saturn;

  saturn.name = "Saturn SL/2";
  saturn.price = 15999.99;
  saturn.speed = 175;

  printf("Name:           %s\n", saturn.name);
  printf("Price (USD):    %f\n", saturn.price);
  printf("Top Speed (km): %d\n", saturn.speed);

  // Now with an initializer! Same field order as in the struct declaration:
  // Risky because if the order of the fields in the struct changes, the initializer will be wrong.
  struct car saturn2 = {"Saturn SL/2", 16000.99, 175};

  printf("Name:      %s\n", saturn2.name);
  printf("Price:     %f\n", saturn2.price);
  printf("Top Speed: %d km\n", saturn2.speed);

  // Independent of the order in the struct
  // Missing field designators are initialized to zero
  struct car saturn3 = {.speed=175, .name="Saturn SL/2"};

  printf("Name:      %s\n", saturn3.name);
  printf("Price:     %f\n", saturn3.price);
  printf("Top Speed: %d km\n", saturn3.speed);

  return 0;
}
