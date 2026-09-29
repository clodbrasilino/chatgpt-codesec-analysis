#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>

#define CHAR_SET_SIZE 256

char find_first_repeated(const char *str)
{
    if (str == NULL)
    {
        return '\0';
    }

    int seen[CHAR_SET_SIZE] = {0};
    size_t i;

    for (i = 0; str[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)str[i];
        if (seen[c])
        {
            return (char)c;
        }
        seen[c] = 1;
    }

    return '\0';
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;
    char result;

    printf("Enter a string: ");
    
    line_length = getline(&buffer, &buffer_size, stdin);
    
    if (line_length == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (line_length > 0 && buffer[line_length - 1] == '\n')
    {
        buffer[line_length - 1] = '\0';
    }

    result = find_first_repeated(buffer);

    if (result != '\0')
    {
        printf("First repeated character: %c\n", result);
    }
    else
    {
        printf("No repeated character found\n");
    }

    free(buffer);
    return 0;
}