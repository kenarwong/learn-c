#pragma once

#include "headers.h"
#include "header_t.h"

void *alloc(size_t size);
void free(void *ptr);

// void *get_free_block(size_t size);
// int sbrk(int increment);
