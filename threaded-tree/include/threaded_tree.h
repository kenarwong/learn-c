#pragma once

#include "headers.h"

#define MAX_LENGTH 32
#define NUL -1

typedef struct {
  char key;
  int thread;
} node;

node **maketree(char key);
void setleft(char key, int parent_index);
void setright(char key, int parent_index);
void traverse(node **arr);
