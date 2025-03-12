#include "headers.h"
#include "threaded_tree.h"

void print_tree(node **arr);

int main() {
  node **arr;
  if ((arr = maketree('a')) == NULL) {
    return -1;
  }

  // // b e c d a f
  // setleft('b', 0);
  // setright('c', 1);
  // setright('d', 4);
  // setleft('e', 4);
  // setright('f', 0);

  // // a b c d e f
  // setright('b', 0);
  // setright('c', 2);
  // setright('d', 6);
  // setright('e', 14);

  // // e d c b a
  // setleft('b', 0);
  // setleft('c', 1);
  // setleft('d', 3);
  // setleft('e', 7);

  // // e c f b d a g
  // setleft('b', 0);
  // setleft('c', 1);
  // setright('d', 1);
  // setleft('e', 3);
  // setright('f', 3);
  // setright('g', 0);

  // // e c f b d a
  // setleft('b', 0);
  // setright('d', 1);
  // setleft('c', 1);
  // setright('f', 3);
  // setleft('e', 3);

  // d b a e g c h f i
  setleft('b', 0);
  setright('c', 0);
  setleft('d', 1);
  setleft('e', 2);
  setright('f', 2);
  setright('g', 5);
  setleft('h', 6);
  setright('i', 6);

  // // d b e c a f
  // setleft('b', 0);
  // setright('c', 1);
  // setleft('d', 1);
  // setleft('e', 4);
  // setright('f', 0);

  #ifndef NDEBUG
  print_tree(arr);
  #endif

  traverse(arr);

  for (int i = 0; i < MAX_LENGTH; i++) {
    if (arr[i]) {
      free(arr[i]);
    }
  }
  free(arr);
  return 0;
}

void print_tree(node **arr) {
  printf("\n");
  printf("--- Printing tree ---\n");

  for(int i = 0; i < MAX_LENGTH; i++) {
    if (!arr[i]) {
      continue;
    }
    printf("arr[%d][0]: %c\n", i, arr[i]->key);
    printf("arr[%d][1]: %d\n", i, arr[i]->thread);
  }
}