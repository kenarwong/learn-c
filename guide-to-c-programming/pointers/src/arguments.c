#include <stdio.h>

/* In the case of a function call.
   one of the copies is stored in a pointer variable out in the calling scope, 
   and the other is stored in a pointer variable that is the parameter of the function.
*/

void increment(int *p)  // note that it accepts a pointer to an int
{
    *p = *p + 1;        // add one to the thing p points to
}

int main(void)
{
    int i = 10;
    int *j = &i;  // note the address-of; turns it into a pointer to i

    printf("i is %d\n", i);        // prints "10"
    printf("i is also %d\n", *j);  // prints "10"

    increment(j);                  // j is an int*--to i

    printf("i is %d\n", i);        // prints "11"!

    // or, equivalently:
    printf("i is %d\n", i);  // prints "11"
    increment(&i);
    printf("i is %d\n", i);  // prints "12"!
}