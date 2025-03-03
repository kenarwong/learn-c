#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 5
#define COLS 10

typedef __uint8_t d_t[3];
typedef d_t RowArray[3];

int multi[ROWS][COLS];

//void set_value(void *start, int size, int dim2, int row, int col, __uint8_t(value)[3]);
void set_value(void *start, int size, int dim2, int row, int col, d_t value);
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
  int cols = 4;
  int size = 3;
  void *ptr = calloc(rows * cols, size);
  // void *p = calloc(rows * cols, size);
  // int (*ptr)[cols] = p; // change pointer to array of arrays
  //memset(ptr, 1, rows*cols*size);

  print_matrix(ptr, size, rows, cols);

  // printf("--- Set Value ---\n");
  // set_value(ptr, size, cols, 5, 0, 0xffffff);
  // printf("---\n");

  printf("--- Set Value ---\n");
  set_value(ptr, size, cols, 4, 1, (__uint8_t[3]){0xab,0xcd,0xef});
  printf("---\n");

  printf("--- Arbitrary-sized Array ---\n");
  print_matrix(ptr, size, rows, cols);

  printf("--- Set Value ---\n");
  set_value(ptr, size, cols, 2, 0, (__uint8_t[3]){0xfe,0xdc,0xba});
  printf("---\n");

  printf("--- Set Value ---\n");
  set_value(ptr, size, cols, 0, 2, (__uint8_t[3]){0xff,0x00,0xff});
  printf("---\n");

  printf("--- Set Value ---\n");
  set_value(ptr, size, cols, 0, 1, (__uint8_t[3]){0x00,0xff,0x00});
  printf("---\n");

  printf("--- Arbitrary-sized Array ---\n");
  print_matrix(ptr, size, rows, cols);

  free(ptr);

  return 0;
}

void set_d_t(d_t ptr, d_t value) {
  // *ptr = value[0];
  // *(ptr+1) = value[1];
  // *(ptr+2) = value[2];
  ptr[0] = value[0];
  ptr[1] = value[1];
  ptr[2] = value[2];
}

// To index a multi-dimensional array
//    dim1 is not necessary (number of rows)
// Refer to array-parameters.c: print_2D_array(int a[][3])
//    Only column size is necessary
void set_value(void *start, int size, int dim2, int row, int col, d_t value)
{

  printf("row: %d, col: %d, size: %i\n", row, col, size);

  int row_size = dim2 * size;
  printf("row_size: %d\n", row_size);

  void *row_i = start + row * row_size;
  void *item_i = row_i + col * size;
  printf("row_i: %p, item_i: %p\n", row_i, item_i);

  // can use memcpy with <string.h>
  // memcpy(item_i, value, 3);

  // can use typedef and array index notation
  // RowArray *array = (RowArray *)start;

  // printf("array: %p, start: %p\n", (void *)array, (void *)start);
  // printf("array[%d]: %p, array[%d][%d]: %p\n", row, (void *)array[row], row, col, (void *)array[row][col]);

  // array[row][col][0] = value[0];
  // array[row][col][1] = value[1];
  // array[row][col][2] = value[2];

  // can use short-hand pointer types instead of typedef
  // typedef __uint8_t d_t[3];
  d_t(*ptr)[dim2] = start;
  // __uint8_t(*ptr)[dim2][3] = start;

  // // stiil can use array index notation
  // ptr[row][col][0] = value[0];
  // ptr[row][col][1] = value[1];
  // ptr[row][col][2] = value[2];
  set_d_t(ptr[row][col], value);

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
        printf("%02x%02x%02x ", c1,c2,c3);
      }

      ptr += size;
    }

    printf("\n");
  }
}