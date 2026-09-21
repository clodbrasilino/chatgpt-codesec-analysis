#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

size_t string_length(const char *str)
{
    if (str == NULL)
    {
        return 0;
    }
    
    size_t length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        if (feof(stdin))
        {
            fprintf(stderr, "End of input reached\n");
        }
        else
        {
            fprintf(stderr, "Error reading input: %s\n", strerror(errno));
        }
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    
    if (len == sizeof(buffer) && buffer[len - 1] != '\n')
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }
    
    printf("Length of the string: %zu\n", string_length(buffer));
    
    return EXIT_SUCCESS;
}