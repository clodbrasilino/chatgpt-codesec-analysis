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
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }
    
    printf("Length of the string: %zu\n", string_length(buffer));
    
    return EXIT_SUCCESS;
}