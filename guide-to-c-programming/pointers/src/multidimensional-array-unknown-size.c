#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    int nrows = 5;     /* Both nrows and ncols could be evaluated */
    int ncols = 10;    /* or read in at run time */
    int row;
    int **rowptr;
    rowptr = malloc(nrows * sizeof(int *));
    if (rowptr == NULL)
    {
        puts("\nFailure to allocate room for row pointers.\n");
        exit(0);
    }

    printf("\n\n\nIndex   Pointer(hex)   Pointer(dec)   Diff.(dec)");

    for (row = 0; row < nrows; row++)
    {
        rowptr[row] = malloc(ncols * sizeof(int));
        if (rowptr[row] == NULL)
        {
            printf("\nFailure to allocate for row[%d]\n",row);
            exit(0);
        }
        printf("\n%d         %p         %d", row, (void *)rowptr[row], (unsigned)rowptr[row]);
        if (row > 0)
        printf("              %d",(int)(rowptr[row] - rowptr[row-1]));
    }

    printf("\n");

    //      To get the array of pointers             1     call
    //      To get space for the rows                5     calls
    //                       Total                   6     calls

    // array notation still works
    // but does not mean that the data in the "two dimensional array" is contiguous in memory
    rowptr[0][1] = 176;
    printf("rowptr[0][1]: %d\n", rowptr[0][1]);

    for (row = 0; row < nrows; row++) {
        free(rowptr[row]);
    }
    free(rowptr);

    return 0;
}