#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

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
    ssize_t read;
    char result;

    printf("Enter a string: ");
    fflush(stdout);

    read = getline(&buffer, &buffer_size, stdin);

    if (read == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (read > 0 && buffer != NULL && buffer[read - 1] == '\n')
    {
        buffer[read - 1] = '\0';
    }

    if (buffer != NULL)
    {
        result = find_first_repeated(buffer);

        if (result != '\0')
        {
            printf("First repeated character: %c\n", result);
        }
        else
        {
            printf("No repeated character found\n");
        }
    }

    free(buffer);
    return 0;
}