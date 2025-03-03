#include <stdio.h>
#include <stdlib.h>
#define ROWS 5
#define COLS 10

int multi[ROWS][COLS];

void set_value(void *start, int size, int dim2, int row, int col, unsigned value);
void print_matrix(void *start, int size, int rows, int cols);

int main(void)
{
  int row, col;
  for (row = 0; row < ROWS; row++)
  {
    for (col = 0; col < COLS; col++)
    {
      multi[row][col] = row * col;
    }
  }

  for (row = 0; row < ROWS; row++)
  {
    for (col = 0; col < COLS; col++)
    {
      printf("\n%d  ", multi[row][col]);
      printf("%d ", *(*(multi + row) + col));
      // We can replace *(*(multi + row) + col) with *(X + col)
      //    X is the start of a row, col is an individual int
      //    The difference between [X+col] and [X+col+1], is sizeof(int)
      //    Each increment in column is an integer
      // multi + row, multi is the start of the multi-dimensional array
      //    row is an entire row of ints: COLS*sizeof(int)
      //    The difference between [multi+row] and [multi+row+1] is size COLS*sizeof(int)
    }
  }

  printf("\n");

  // 5 values must be known:
  //  - starting address of array (multi)
  //  - size of the type of element (sizeof(int))
  //  - 2nd dimension of array (COLS) 
  //      - 1st dimension is not necessary (ROWS)
  //  - index value of first dimension (row)
  //  - index value of the second dimension (col)

  printf("--- Arbitrary-sized Array ---\n");

  // array of arbitrary size
  int rows = 6;
  int cols = 3;
  int size = 3;
  void *ptr = calloc(rows * cols, size);
  //memset(ptr, 1, rows*cols*size);

  print_matrix(ptr, size, rows, cols);

  // printf("--- Set Value ---\n");
  // set_value(ptr, size, cols, 5, 0, 0xffffff);
  // printf("---\n");

  printf("--- Set Value ---\n");
  set_value(ptr, size, cols, 4, 1, 0xabcdef);
  printf("---\n");

  printf("--- Arbitrary-sized Array ---\n");
  print_matrix(ptr, size, rows, cols);

  printf("--- Set Value ---\n");
  set_value(ptr, size, cols, 2, 0, 0xfedcba);
  printf("---\n");

  printf("--- Set Value ---\n");
  set_value(ptr, size, cols, 0, 2, 0xff00ff);
  printf("---\n");

  printf("--- Arbitrary-sized Array ---\n");
  print_matrix(ptr, size, rows, cols);

  free(ptr);

  return 0;
}

// To index a multi-dimensional array
//    dim1 is not necessary (number of rows)
// Refer to array-parameters.c: print_2D_array(int a[][3])
//    Only column size is necessary
void set_value(void *start, int size, int dim2, int row, int col, unsigned value)
{

  printf("row: %d, col: %d, size: %i\n", row, col, size);

  int row_size = dim2 * size;
  printf("row_size: %d\n", row_size);

  void *row_i = start + row * row_size;
  void *item_i = row_i + col * size;
  printf("row_i: %p, item_i: %p\n", row_i, item_i);

  *(unsigned *)(item_i) = value;

  return;
}

void print_matrix(void *start, int size, int rows, int cols)
{
  void *ptr = start;
  __uint8_t c1;
  __uint8_t c2;
  __uint8_t c3;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      __uint8_t c1 = *((__uint8_t *)ptr);
      __uint8_t c2 = *((__uint8_t *)(ptr + 1));
      __uint8_t c3 = *((__uint8_t *)(ptr + 2));

      if (c1 == 0 &&
          c2 == 0 &&
          c3 == 0) {
        printf(" NULL  ");
      } else {
        printf("%x%x%x ", c1,c2,c3);
      }

      ptr += size;
    }

    printf("\n");
  }
}