#include <stdio.h>

void foo();
void foo(void);  // Not the same!

int main(void)
{
    foo();
}

void foo()  // Should really have a `void` in there
{
    printf("Hello, world!\n");
}