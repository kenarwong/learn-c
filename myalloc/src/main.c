#include "headers.h"
#include "alloc.h"

int main() {
  // Allocate initial blocks
  printf("------ Allocating 64 bytes ------\n");
  void *ptr1 = my_alloc(64);
  printf("\n\n");

  printf("------ Allocating 128 bytes ------\n");
  void *ptr2 = my_alloc(128);
  printf("\n\n");

  printf("------ Allocating 256 bytes ------\n");
  void *ptr3 = my_alloc(256);
  printf("\n\n");

  printf("------ Allocating 96 bytes ------\n");
  void *ptr4 = my_alloc(96);
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
  printf("------ Allocating 112 bytes to second block ------\n");
  void *ptr5 = my_alloc(112);
  printf("\n\n");

  display_blocks();
  display_free_list();

  // Free end block and check if consecutive blocks are freed
  printf("------ Freeing second block ------\n");
  free(ptr5);
  printf("\n\n");

  display_blocks();
  display_free_list();

  printf("------ Freeing fourth block ------\n");
  free(ptr4);
  printf("\n\n");

  display_blocks();
  display_free_list();

  clear_heap();

  return 0;
}