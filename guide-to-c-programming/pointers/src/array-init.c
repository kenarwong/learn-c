#include <stdio.h>

int main(void)
{
    int i;
    int a[5] = {22, 37, 3490, 18, 95};  // Initialize with these values

    for (i = 0; i < 5; i++) {
        printf("%d\n", a[i]);
    }

    int b[5] = {22, 37, 3490};

    // is the same as:
    int c[5] = {22, 37, 3490, 0, 0};

    // common to initialize an array to all zeros
    int d[100] = {0};


    // Initialize an array with a designated initializer
    // Will fill in the rest with zeros
    int e[10] = {0, 11, 22, [5]=55, 66, 77};  // 0, 11, 22, 0, 0, 55, 66, 77, 0, 0

    #define COUNT 5

    int f[COUNT] = {[COUNT - 3] = 3, 2, 1}; // 0, 0, 3, 2, 1

    for (i = 0; i < COUNT; i++)
    {
      printf("%d\n", f[i]);
    }

    int g[3] = {22, 37, 3490};

    // is the same as:
    int h[] = {22, 37, 3490};  // Left the size off!
}