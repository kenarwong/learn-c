#include "threaded_tree.h"

node **arr = NULL;
node *leftmost(node **arr, int *i);

node **maketree(char key) {
  if (arr) {
    return arr;
  }

  arr = calloc(MAX_LENGTH, sizeof(node*));
  if (!arr) {
    return NULL;
  }

  for (int i = 0; i < MAX_LENGTH; i++) {
    arr[i] = NULL;
    // printf("arr[%d]: %p\n", i, (void *) arr[i]);
  }

  #ifndef NDEBUG
  printf("sizeof(node*): %lu\n", sizeof(node*));
  #endif

  arr[0] = calloc(1, sizeof(node));
  if (!arr[0]) {
    return NULL;
  }

  arr[0]->key = key;
  arr[0]->thread = NUL;

  return arr;
}

void setleft(char key, int parent_index) {
  int i = (parent_index << 1) + 1;

  #ifndef NDEBUG
  printf("--- setleft ---\n");
  printf("arr: %p\n", (void *) arr);
  printf("arr[parent_index]: %p\n", (void *) arr[parent_index]);
  printf("arr[parent_index]->key: %c\n", (arr[parent_index])->key);
  printf("arr[parent_index]->thread: %d\n", (arr[parent_index])->thread);
  printf("i: %d\n", i);
  printf("left_child: %p\n", (void *) arr[i]);
  #endif  

  node *left_child = arr[i];

  if (left_child) {
    left_child->key = key;

    #ifndef NDEBUG
    printf("left_child: %p\n", (void *) left_child);
    printf("left_child->key: %c\n", left_child->key);
    printf("left_child->thread: %d\n", left_child->thread);
    #endif

    return;
  }

  left_child = malloc(sizeof(node));
  if (!left_child) {
    return;
  }

  left_child->key = key;
  left_child->thread = parent_index;
  arr[i] = left_child;

  #ifndef NDEBUG
  printf("left_child: %p\n", (void *) left_child);
  printf("left_child->key: %c\n", left_child->key);
  printf("left_child->thread: %d\n", left_child->thread);
  #endif
}

void setright(char key, int parent_index) {
  int i = (parent_index << 1) + 2;

  #ifndef NDEBUG
  printf("--- setright ---\n");
  printf("arr: %p\n", (void *) arr);
  printf("arr[parent_index]: %p\n", (void *) arr[parent_index]);
  printf("arr[parent_index]->key: %c\n", (arr[parent_index])->key);
  printf("arr[parent_index]->thread: %d\n", (arr[parent_index])->thread);
  printf("i: %d\n", i);
  printf("right_child: %p\n", (void *) arr[i]);
  #endif

  node *right_child = arr[i];

  if (right_child) {
    right_child->key = key;

    #ifndef NDEBUG
    printf("right_child: %p\n", (void *) right_child);
    printf("right_child->key: %c\n", right_child->key);
    printf("right_child->thread: %d\n", right_child->thread);
    #endif

    return;
  }

  right_child = malloc(sizeof(node));
  if (!right_child) {
    return;
  }

  node *p = arr[parent_index];

  right_child->key = key;
  right_child->thread = p->thread; // thread of parent
  arr[i] = right_child;

  p->thread = NUL; // thread of parent is now NUL
  
  #ifndef NDEBUG
  printf("right_child: %p\n", (void *) right_child);
  printf("right_child->key: %c\n", right_child->key);
  printf("right_child->thread: %d\n", right_child->thread);
  #endif
}

void traverse(node **arr) {
  if (!arr) {
    return;
  }

  int i = 0;

  // leftmost child of root
  node *p = leftmost(arr, &i);

  // traverse
  do {
    #ifndef NDEBUG
    printf("--- traverse ---\n");
    printf("i: %d\n", i);
    #endif

    printf("arr[%d]->key: %c\n", i, p->key);

    #ifndef NDEBUG
    printf("arr[%d]->thread: %d\n", i, p->thread);
    #endif

    // next
    if (p->thread != NUL) {
      i = p->thread;
      p = arr[p->thread];
    } else {
      // get right child
      i = 2*i + 2;
      node *right = arr[i];

      #ifndef NDEBUG
      printf("i: %d\n", i);
      printf("right: %p\n", (void *) right);
      #endif

      if (!right) {
        // if null, then end
        return;
      } else {
        // right child is not yet in-order successor
        // convert to in order sucessor with leftmost
        p = leftmost(arr, &i);
      }
    }
  } while (p);
}

node *leftmost(node **arr, int *i) {
  #ifndef NDEBUG
  printf("--- leftmost ---\n");
  #endif  
  
  int next = 2*(*i) + 1;
  node *p = arr[next];

  while (p) {
    *i = next;

    #ifndef NDEBUG
    printf("i: %d\n", *i);
    printf("next: %d\n", next);
    printf("p: %p\n", (void *) p);
    printf("p->key: %c\n", p->key);
    printf("p->thread: %d\n", p->thread);
    #endif

    next = 2*(*i) + 1;
    p = arr[next];
  }

  return arr[*i];
}