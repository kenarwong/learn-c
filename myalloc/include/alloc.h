#pragma once

#include "headers.h"
#include "header_t.h"

void *my_alloc(size_t size);
void free(void *ptr);

void *sbrk(int increment);
void *get_free_block(size_t size);

void clear_heap();
void display_blocks();
