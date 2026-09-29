#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    char *result;
    size_t input_len;
    size_t result_idx = 0;
    size_t i;
    int capitalize_next = 1;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        if (input[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                result[result_idx] = (char)toupper((unsigned char)input[i]);
                capitalize_next = 0;
            } else {
                result[result_idx] = input[i];
            }
            result_idx++;
        }
    }

    result[result_idx] = '\0';
    return result;
}

int main(void)
{
    const char *input = "convert_snake_case_to_camel_case";
    char *output;

    output = snake_to_camel(input);
    if (output == NULL) {
        fprintf(stderr, "Error: conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Snake case: %s\n", input);
    printf("Camel case: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}