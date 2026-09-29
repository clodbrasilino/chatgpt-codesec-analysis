#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_whitespace(const char *input, size_t max_len)
{
    if (input == NULL)
    {
        return NULL;
    }

    size_t length = strnlen(input, max_len);
    char *result = malloc(length + 1);

    if (result == NULL)
    {
        return NULL;
    }

    size_t write_index = 0;

    for (size_t read_index = 0; read_index < length; read_index++)
    {
        if (!isspace((unsigned char)input[read_index]))
        {
            result[write_index] = input[read_index];
            write_index++;
        }
    }

    result[write_index] = '\0';
    return result;
}

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t chars_read;

    printf("Enter a string: ");
    
    chars_read = getline(&input, &input_size, stdin);
    
    if (chars_read == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *cleaned = remove_whitespace(input, (size_t)chars_read);
    
    free(input);

    if (cleaned == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", cleaned);
    free(cleaned);

    return EXIT_SUCCESS;
}