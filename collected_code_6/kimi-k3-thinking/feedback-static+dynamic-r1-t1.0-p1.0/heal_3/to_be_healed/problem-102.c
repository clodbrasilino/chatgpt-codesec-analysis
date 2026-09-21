#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static size_t bounded_strlen(const char *s, size_t max_len)
{
    const char *nul = memchr(s, '\0', max_len);

    if (nul == NULL)
    {
        return max_len;
    }
    return (size_t)(nul - s);
}

char *snake_to_camel(const char *input, size_t max_len)
{
    char *output;
    size_t input_len;
    size_t i;
    size_t j;
    int uppercase_next;

    if (input == NULL || max_len == 0)
    {
        return NULL;
    }

    input_len = bounded_strlen(input, max_len);
    output = malloc(input_len + 1);
    if (output == NULL)
    {
        return NULL;
    }

    j = 0;
    uppercase_next = 1;
    for (i = 0; i < input_len; i++)
    {
        if (input[i] == '_')
        {
            uppercase_next = 1;
        }
        else if (uppercase_next)
        {
            output[j++] = (char)toupper((unsigned char)input[i]);
            uppercase_next = 0;
        }
        else
        {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';

    return output;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *result;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return EXIT_FAILURE;
    }

    len = bounded_strlen(input, sizeof(input));
    if (len == sizeof(input) - 1 && input[len - 1] != '\n')
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        if (c != EOF && c != '\n')
        {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != EOF && c != '\n')
            {
            }
            fprintf(stderr, "Error: input exceeds maximum length\n");
            return EXIT_FAILURE;
        }
    }

    input[strcspn(input, "\r\n")] = '\0';

    result = snake_to_camel(input, sizeof(input));
    if (result == NULL)
    {
        fprintf(stderr, "Error: conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}