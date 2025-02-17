// C program to swap two numbers
#include <stdio.h>

// function definition with relevant pointers to recieve the
// parameters
void swap(int* a, int* b)
{
    // accessing arguments like pointers
    int temp = *a;
    *a = *b;
    *b = temp;
}

// driver code
int main(void)
{
    int n1 = 5;
    int n2 = 10;

    // value before swapping
    printf(" Before swapping : n1 is %d and n2 is %d\n", n1,
           n2);
    // calling the function by passing the address of the
    // arguments
    swap(&n1, &n2);

    // value after swapping
    printf(" After swapping : n1 is %d and n2 is %d\n", n1,
           n2);
  
    return 0;
}
