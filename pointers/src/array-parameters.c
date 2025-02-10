#include <stdio.h>

// All these methods are equivalent
// void times2(int *a, int len)
// void times3(int a[], int len)
// void times4(int a[5], int len)

// Passing as a pointer to the first element
// Most common way to pass an array
void times2(int *a, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d\n", a[i] * 2);
}

// Same thing, but using array notation
void times3(int a[], int len)
{
    for (int i = 0; i < len; i++)
        printf("%d\n", a[i] * 3);
}

// Same thing, but using array notation with size
// Compiler does not care or enforce the size
void times4(int a[5], int len)
{
    for (int i = 0; i < len; i++)
        printf("%d\n", a[i] * 4);
}

// Passing an array is equivalent to passing a pointer
// Values modified will be reflected in the original array
void double_array(int *a, int len)
{
    // Multiply each element by 2
    //
    // This doubles the values in x in main() since x and a both point
    // to the same array in memory!

    for (int i = 0; i < len; i++)
        a[i] *= 2;  // Even though parameter is int *a, This is totally allowed.

}

// These two are equivalent
// void print_2D_array(int a[2][3])
// void print_2D_array(int a[][3])

void print_2D_array(int a[2][3])
{
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++)
            printf("%d ", a[row][col]);
        printf("\n");
    }
}

int main(void)
{
    int x[5] = {11, 22, 33, 44, 55};

    times2(x, 5);
    times3(x, 5);
    times4(x, 5);

    // x is being passed as a pointer
    double_array(x, 5);

    // x has been modified by double_array()
    for (int i = 0; i < 5; i++)
        printf("%d\n", x[i]);  // 2, 4, 6, 8, 10!

    int x2[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    print_2D_array(x2);
}