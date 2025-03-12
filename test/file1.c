#include <stdio.h>

static int x = 10;
int y;

static int a() {
  return 10;
}

int b() {
  y = x;
  return a();
}

void file1() {

  printf("%d",x); // 10
  printf("%d",a()); // 10
}

