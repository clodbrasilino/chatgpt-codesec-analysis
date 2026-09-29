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

    input_len = strlen(input);
    output = malloc(input_len + 1);
    if (output == NULL)
    {
        return NULL;
    }

    j = 0;
    uppercase_next = 0;
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
    const char *test_strings[] = {
        "hello_world",
        "convert_snake_case_to_camel_case",
        "single",
        "with__double_underscores"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    char *result;

    for (i = 0; i < num_tests; i++)
    {
        result = snake_to_camel(test_strings[i]);
        if (result == NULL)
        {
            fprintf(stderr, "Error: conversion failed for input \"%s\"\n", test_strings[i]);
            return EXIT_FAILURE;
        }

        printf("Input:  %s\n", test_strings[i]);
        printf("Output: %s\n\n", result);

        free(result);
        result = NULL;
    }

    return EXIT_SUCCESS;
}