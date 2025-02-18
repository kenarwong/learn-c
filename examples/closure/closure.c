#include <stdio.h>

int main() {
    int a = 1;
    int g() { return a + 2; };
    
    printf("%d\n", g());

    return 0;
} 
