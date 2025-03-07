#include <stdio.h>

char strA[80] = "A string to be used for demonstration purposes";
// char strB[80];
char strB[80] = "12345678901234567890123456789012345678901234567890";

int main(void)
{

    char *pA;     /* a pointer to type character */
    char *pB;     /* another pointer to type character */
    puts(strA);   /* show string A */
    pA = strA;    /* point pA at string A */
    puts(pA);     /* show what pA is pointing to */
    pB = strB;    /* point pB at string B */


    putchar('\n');       /* move down one line on the screen */
    while(*pA != '\0')   /* line A (see text) */
    {
        *pB++ = *pA++;   /* line B (see text) */
    }
    *pB = '\0';          /* line C (see text) */
    puts(strB);          /* show strB on screen */

    // read rest of string
    pB++;
    puts(pB);          

    return 0;
}