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
  *   5 0 0 0 0 0 0
  *   0 6 8 0 4 2 0
  *   0 0 0 0 3 3 0
  *   9 0 0 5 0 0 3
  *   0 0 0 0 0 0 0
  *   0 2 0 1 0 0 0
  */

  int n = 6;
  int nnz = 12;

  int r[7] = {0,1,5,7,10,10,12};
  int c[12] = {0,1,2,4,5,4,5,0,3,6,1,3};
  int v[12] = {5,6,8,4,2,3,3,9,5,3,2,1};

  csr_t matrix = {
      .n = n,
      .nnz = nnz,
      .r = r,
      .c = c,
      .v = v,
  };

  int vector[7] = {2,7,8,5,7,1,4};
  int result[n];

  matrix_vector_multiply(&matrix,vector,result);

  for (int row = 0; row < 6; row++) {
    printf("%d\n", result[row]);
  }

  return 0;
}