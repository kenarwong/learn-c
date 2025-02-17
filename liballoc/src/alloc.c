#include "alloc.h"

// header_t *head = NULL, *tail = NULL;

void *alloc(size_t size) {
  size_t total_size;
  void *block;
  header_t *header;

  if (!size)
    return NULL;
  
  // get next free block

  // if no free block, allocate new block
  total_size = size + sizeof(header_t);
  printf("alloc\n");
}

void free(void *ptr) {
  printf("free\n");
}