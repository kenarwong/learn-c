#pragma once

#include "headers.h"

typedef char ALIGN[64];

union header {
  struct {
    size_t size;
    unsigned is_free;
    union header *next_free;
    union header *prev_free;
    union header *next;
    union header *prev;
  } s;
  ALIGN stub;
};

typedef union header header_t;