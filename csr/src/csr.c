#include <stdio.h>

typedef struct {
  int n, nnz;
  int *r;
  int *c;
  int *v;
} csr_t;

void matrix_vector_multiply(csr_t *matrix, int *vector, int* result) {
  for (int row = 0; row < matrix->n; row++) {
    result[row] = 0;
    for (int j = matrix->r[row]; j < matrix->r[row+1]; j++) {
      int col = matrix->c[j];
      result[row] += matrix->v[j] * vector[col]; 
    }
  }
  return;
}

int main(void) {

  /*
  *   3 0 0 0 1 0
  *   0 4 1 0 5 9
  *   0 0 0 2 0 6
  *   5 0 0 3 0 0
  *   5 0 0 0 8 0
  *   0 0 0 9 7 0
  */

  int *r = (int[]){0,2,6,8,10,12,14};
  int *c = (int[]){0,4,1,2,4,5,3,5,0,3,0,4,3,4};
  int *v = (int[]){3,1,4,1,5,9,2,6,5,3,5,8,9,7};

  csr_t matrix = {
    .n = 6,
    .nnz = 14,
    .r = r,
    .c = c,
    .v = v,
  };

  int vector[6] = {1,4,2,8,5,7};
  int result[6];

  matrix_vector_multiply(&matrix,vector,result);

  for (int row = 0; row < 6; row++) {
    printf("%d\n", result[row]);
  }

  return 0;
}