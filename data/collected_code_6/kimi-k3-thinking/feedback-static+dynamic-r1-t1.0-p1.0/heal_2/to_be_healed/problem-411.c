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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);

    result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (c == '_') {
            capitalize_next = 1;
            continue;
        }

        if (capitalize_next) {
            result[result_idx++] = (char)toupper(c);
            capitalize_next = 0;
        } else {
            result[result_idx++] = (char)c;
        }
    }

    result[result_idx] = '\0';
    return result;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    const char *input;
    char *output;
    size_t len;

    if (argc > 1) {
        input = argv[1];
    } else if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[--len] = '\0';
        }
        input = buffer;
    } else {
        input = "convert_snake_case_to_camel_case";
    }

    output = snake_to_camel(input);
    if (output == NULL) {
        fprintf(stderr, "Error: conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    return EXIT_SUCCESS;
}