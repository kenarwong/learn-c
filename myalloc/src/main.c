#include "headers.h"
#include "alloc.h"

int main() {
  // Allocate initial blocks
  printf("------ Allocating 10 bytes ------\n");
  void *ptr1 = my_alloc(10);
  printf("\n\n");

  printf("------ Allocating 20 bytes ------\n");
  void *ptr2 = my_alloc(20);
  printf("\n\n");

  printf("------ Allocating 30 bytes ------\n");
  void *ptr3 = my_alloc(30);
  printf("\n\n");

  printf("------ Allocating 10 bytes ------\n");
  void *ptr4 = my_alloc(10);
  printf("\n\n");

  display_blocks();
  display_free_list();

  // Free blocks
  printf("------ Freeing first block ------\n");
  free(ptr1);
  printf("\n\n");

  display_blocks();
  display_free_list();

  printf("------ Freeing second block ------\n");
  free(ptr2);
  printf("\n\n");

  display_blocks();
  display_free_list();

  printf("------ Freeing third block ------\n");
  free(ptr3);
  printf("\n\n");

  display_blocks();
  display_free_list();

  // Allocate non-contiguous block
  printf("------ Allocating 20 bytes ------\n");
  void *ptr5 = my_alloc(20);
  printf("\n\n");

  display_blocks();
  display_free_list();

  // Free end block and check if consecutive blocks are freed
  printf("------ Freeing fourth block ------\n");
  free(ptr4);
  printf("\n\n");

  display_blocks();
  display_free_list();

  clear_heap();

  return 0;
}