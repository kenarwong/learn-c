#include <stdio.h>
#include <string.h>

// void *memcpy(void *s1, void *s2, size_t n);

void *my_memcpy(void *dest, void *src, int byte_count)
{
    // Convert void*s to char*s
    char *s = src, *d = dest;

    // Decrement byte_count until it becomes false (0)
    // Remember that with post-decrement, the value of the expression is computed (for while to use) and then the variable is decremented.
    while (byte_count--) {
        // Now that we have char*s, we can dereference and copy them

        // Copy the byte, but do it with post-increment
        *d++ = *s++;
    }

    // Most of these functions return the destination, just in case
    // that's useful to the caller.
    return dest;
}

int main(void)
{
    char s[] = "Goats!";
    char t[100];

    memcpy(t, s, 7);  // Copy 7 bytes--including the NUL terminator!

    printf("%s\n", t);  // "Goats!"

    int a[] = {11, 22, 33};
    int b[3];

    memcpy(b, a, 3 * sizeof(int));  // Copy 3 ints of data

    printf("%d\n", b[1]);  // 22

    // Conversion 
    char c = 'X';  // A single char

    void *p = &c;  // p points to the 'X'
    char *q = p;   // q also points to the 'X'

    // printf("%c\n", *p);  // ERROR--cannot dereference void*!
    printf("%c\n", *q);  // Prints "X"
}