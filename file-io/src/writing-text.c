#include <stdio.h>

int main(void)
{
    FILE *fp;
    int x = 32;

    fp = fopen("output.txt", "w");
    
    // stdout is a FILE* that represents the standard output stream
    // Will do the same thing as the above line, but write to the console
    // fp = stdout;  

    fputc('B', fp);
    fputc('\n', fp);   // newline
    fprintf(fp, "x = %d\n", x);
    fputs("Hello, world!\n", fp);

    fclose(fp);
}