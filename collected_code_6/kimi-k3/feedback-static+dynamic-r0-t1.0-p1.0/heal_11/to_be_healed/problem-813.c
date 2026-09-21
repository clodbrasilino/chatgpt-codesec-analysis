#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

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

static bool read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size == 0)
    {
        return false;
    }
    
    if (fgets(buffer, size, stdin) == NULL)
    {
        if (feof(stdin))
        {
            fprintf(stderr, "End of input reached\n");
        }
        else
        {
            fprintf(stderr, "Error reading input: %s\n", strerror(errno));
        }
        return false;
    }
    
    size_t len = strnlen(buffer, size);
    
    if (len == size && buffer[len - 1] != '\n')
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
        fprintf(stderr, "Input too long\n");
        return false;
    }
    
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    
    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    
    printf("Enter a string: ");
    
    if (!read_line(buffer, sizeof(buffer)))
    {
        return EXIT_FAILURE;
    }
    
    printf("Length of the string: %zu\n", string_length(buffer));
    
    return EXIT_SUCCESS;
}