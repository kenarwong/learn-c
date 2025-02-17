#pragma once

#include "headers.h"

typedef char ALIGN[16];

union header {
  struct {
    size_t size;
    union header *next_free;
    union header *prev_free;
    union header *next;
    union header *prev;
  } s;
  ALIGN stub;
};

typedef union header header_t;