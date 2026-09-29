#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    char *output;
    size_t input_len;
    size_t i;
    size_t j;
    int uppercase_next;

    if (input == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
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

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\r\n")] = '\0';

    result = snake_to_camel(input);
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