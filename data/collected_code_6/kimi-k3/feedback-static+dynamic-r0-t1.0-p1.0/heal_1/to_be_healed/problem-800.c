#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_whitespace(const char *input)
{
    if (input == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    char *cleaned = remove_whitespace(input);
    if (cleaned == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", cleaned);
    free(cleaned);

    return EXIT_SUCCESS;
}