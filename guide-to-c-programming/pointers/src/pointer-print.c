#include <stdio.h>

int j, k;
int *ptr;

int main(void)
{
  // printf %p expects void*

    j = 1;
    k = 2;
    ptr = &k;
    printf("\n");
    printf("j has the value %d and is stored at %p\n", j, (void *)&j);
    printf("k has the value %d and is stored at %p\n", k, (void *)&k);
    printf("ptr has the value %p and is stored at %p\n", ptr, (void *)&ptr); // gets a warning because ptr is int* not void*
    printf("The value of the integer pointed to by ptr is %d\n", *ptr);

    return 0;
}
