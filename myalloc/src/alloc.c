#include "alloc.h"

#define MAX_HEAP_SIZE 1024

header_t *head, *tail = NULL;
header_t *free_head, *free_tail = NULL;
char heap[MAX_HEAP_SIZE];
char *program_brk = heap;

void append_to_free_list(header_t *header);
void remove_from_free_list(header_t *header);

void *my_alloc(size_t size) {
  printf("------ START my_alloc ------\n");

  size_t total_size;
  void *block;
  header_t *header;

  if (!size)
    return NULL;
  
  // get next free block
  block = get_free_block(size);
  if (block != (void *) -1) {
    header = block;
    remove_from_free_list(header);
    return (void *)(header + 1);
  }

  // if no free block, allocate new block
  total_size = size + sizeof(header_t);
  printf("total_size: %x\n", total_size);

  // get new block
  block = sbrk(total_size);
  if (block == (void *) -1)
    return NULL;
  printf("block: %x\n", block);

  // create header
  header = block;
  header->s.size = size;
  header->s.is_free = 0;
  header->s.next = header->s.prev = NULL;

  // add to header list
  if (!head) {
    head = tail = header;
  } else {
    header->s.prev = tail;
    tail->s.next = header;
    tail = header;
  }
  
  printf("sizeof(header_t): %x\n", sizeof(header_t));
  // printf("header + sizeof(header_t): %x\n", ((void *)header) + sizeof(header_t));
  printf("sizeof(header_t) + size: %x\n", sizeof(header_t) + size);
  printf("next block: %x\n", (void *)(header + 1) + size);
  printf("------ END my_alloc ------\n");

  return (void *)(header + 1);
}

void free(void *ptr) {
  printf("------ START free ------\n");

  header_t *header;
  void *program_break;

  if (!ptr)
    return;
  printf("ptr: %x\n",ptr);

  // check if memory to free is last block
  header = (header_t *)ptr - 1;
  printf("header: %x\n", header);

  program_break = sbrk(0);
  printf("program_break: %x\n", program_break);

  // add block to free list
  append_to_free_list(header);

  // release block if last block
  if ((char *)ptr + header->s.size == program_break) {
    // delete consecutive free blocks (starting with last block)
    do {
      // update header list
      if (head == tail) {
        head = tail = NULL;
      } else {
        tail = tail->s.prev;
        tail->s.next = NULL;
      }

      // update free list
      remove_from_free_list(header);

      // free block
      sbrk(0 - sizeof(header_t) - header->s.size);

      #ifndef NDEBUG
      program_break = sbrk(0);
      printf("program_break: %x\n", program_break);
      #endif

      // get previous consecutive block
      header = header->s.prev;
    } while (header && header->s.is_free);
  }

  printf("------ END free ------\n");
  return;
}

void *sbrk(int inc) {
  #ifndef NDEBUG
  printf("------ START sbrk ------\n");
  printf("program_brk: %x\n", (char *)program_brk);
  printf("heap: %x\n", (char *)heap);
  printf("max: %x\n", (char *)heap + MAX_HEAP_SIZE);
  #endif

  void *old_program_brk = program_brk;

  #ifndef NDEBUG
  printf("old_program_brk: %x\n", program_brk);
  #endif
   
  if (program_brk + inc > ((char *)heap + MAX_HEAP_SIZE))
    return (void *) -1;
  if (program_brk + inc < (char *)heap)
    return (void *) -1;
  program_brk += inc;

  #ifndef NDEBUG
  printf("program_brk: %x\n", program_brk);
  printf("------ END sbrk ------\n");
  #endif
  return old_program_brk;
}

void *get_free_block(size_t size) {
  printf("------ START get_free_block ------\n");
  printf("size: %x\n", size);

  header_t *curr = free_head;
  while (curr) {
    printf("curr: %x, size: %x, is_free: %d \n", curr, curr->s.size, curr->s.is_free);
    // if (curr->s.is_free && curr->s.size >= size)
    if (curr->s.size >= size)
      return curr;
    curr = curr->s.next_free;
  }

  printf("------ END get_free_block ------\n");
  return (void *) -1;
}

void append_to_free_list(header_t *header) {
  printf("------ START append_to_free_list ------\n");

  header->s.is_free = 1;
  header->s.prev_free = header->s.next_free = NULL;

  if (!free_head) {
    free_head = free_tail = header;
  } else {
    header->s.prev_free = free_tail;
    free_tail->s.next_free = header;
    free_tail = header;
  }

  printf("------ END append_to_free_list ------\n");
  return;
}

void remove_from_free_list(header_t *header) {
  printf("------ START remove_from_free_list ------\n");

  if (free_head == free_tail) {
    free_head = free_tail = NULL;
  } else {
    if (header == free_head) {
      free_head = header->s.next_free;
      free_head->s.prev_free = NULL;
    } else if (header == free_tail) {
      free_tail = header->s.prev_free;
      free_tail->s.next_free = NULL;
    } else {
      header->s.prev_free->s.next_free = header->s.next_free;
      header->s.next_free->s.prev_free = header->s.prev_free;
    }
  }

  header->s.is_free = 0;
  header->s.prev_free = header->s.next_free = NULL;

  printf("------ END remove_from_free_list ------\n");
  return;
}

void clear_heap() {
  head = tail = NULL;
  free_head = free_tail = NULL;
  program_brk = heap;
}

void display_blocks() {
  printf("------ START display_blocks ------\n");

  header_t *curr = head;
  while (curr) {
    printf("curr: %x, size: %x, is_free: %d \n", curr, curr->s.size, curr->s.is_free);
    curr = curr->s.next;
  }

  printf("------ END display_blocks ------\n");
  printf("\n");
  printf("\n");
  return;
}

void display_free_list() {
  printf("------ START display_free_list ------\n");

  header_t *curr = free_head;
  while (curr) {
    printf("curr: %x, size: %x, is_free: %d \n", curr, curr->s.size, curr->s.is_free);
    curr = curr->s.next_free;
  }

  printf("------ END display_free_list ------\n");
  printf("\n");
  printf("\n");
  return;
}