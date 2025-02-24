#include <stdio.h>

struct animal {
    char *name;
    int leg_count, speed;
};

//  original name
//            |
//            v
//      |-----------|
typedef struct animal2 {
    char *name;
    int leg_count, speed;
} animal2;                         // <-- new name

//  Anonymous struct! It has no name!
//         |
//         v
//      |----|
typedef struct {
    char *name;
    int leg_count, speed;
} animal3;                         // <-- new name

typedef struct {
    int x, y;
} point;

int main(void)
{

  //  original name      new name
  //            |         |
  //            v         v
  //      |-----------| |----|
  typedef struct animal animal;

  struct animal y;  // This works
  animal z;         // This also works because "animal" is an alias

  animal2 z2;
  
  //struct animal3 y;  // ERROR: this no longer works--no such struct!
  animal3 z3;

  point p = {.x=20, .y=40};

  printf("%d, %d\n", p.x, p.y);  // 20, 40

  return 0;
}