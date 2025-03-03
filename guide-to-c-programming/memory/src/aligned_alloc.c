#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// alignment with realloc
void *aligned_realloc(void *ptr, size_t old_size, size_t alignment, size_t size)
{
    char *new_ptr = aligned_alloc(alignment, size);

    if (new_ptr == NULL)
        return NULL;

    size_t copy_size = old_size < size? old_size: size;  // get min

    if (ptr != NULL)
        memcpy(new_ptr, ptr, copy_size);
      
        // Note that it always copies data, taking time, 
        // while real realloc() will avoid that if it can. 
        // So this is hardly efficient. 
        // Avoid needing to reallocate custom-aligned data. 

    free(ptr);

    return new_ptr;
}

int main(void)
{
    // Allocate 256 bytes aligned on a 64-byte boundary
    //    The alignment is an integer power of two greater than zero, so 2, 4, 8, 16, etc. 
    //        and you give that to aligned_alloc() before the number of bytes you’re interested in.
    //    The other restriction is that the number of bytes you allocate needs to be a multiple of the alignment.
    char *p = aligned_alloc(64, 256);  // 256 == 64 * 4

    // Copy a string in there and print it
    strcpy(p, "Hello, world!");
    printf("%s\n", p);

    // Free the space
    free(p);
}