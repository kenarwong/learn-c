#include "headers.h"
#include "alloc.h"

int main() {
  void *ptr = alloc(10);
  free(ptr);

  return 0;
}