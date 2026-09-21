#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_INPUT_LEN 256

char *to_lowercase(const char *input, size_t max_len)
{
    char *result;
    size_t i;
    size_t len;

    if (input == NULL || max_len == 0)
    {
        return NULL;
    }

    len = strnlen(input, max_len);
    result = (char *)malloc(len + 1);

    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
        result[i] = (char)tolower((unsigned char)input[i]);
    }

    result[len] = '\0';

    return result;
}

int main(void)
{
    char *input = NULL;
    char *lowercase_str = NULL;
    size_t input_len;
    size_t buffer_size = MAX_INPUT_LEN + 2;
    ssize_t bytes_read;

    input = (char *)malloc(buffer_size);
    if (input == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter a string: ");
    
    bytes_read = getline(&input, &buffer_size, stdin);
    
    if (bytes_read == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }

    input_len = strcspn(input, "\n");

    if (input[input_len] == '\n')
    {
        input[input_len] = '\0';
    }
    else
    {
        if (!feof(stdin))
        {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            fprintf(stderr, "Input too long\n");
            free(input);
            return 1;
        }
        input[input_len] = '\0';
    }

    lowercase_str = to_lowercase(input, MAX_INPUT_LEN + 1);

    if (lowercase_str == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(input);
        return 1;
    }

    printf("Lowercase string: %s\n", lowercase_str);

    free(lowercase_str);
    free(input);

    return 0;
}