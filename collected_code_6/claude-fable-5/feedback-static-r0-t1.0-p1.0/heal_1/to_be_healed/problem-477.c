#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *string_to_lower(const char *input)
{
    size_t len;
    size_t i;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        result[i] = (char)tolower((unsigned char)input[i]);
    }
    result[len] = '\0';

    return result;
}

int main(void)
{
    const char *original = "Hello, World! THIS Is A Test String.";
    char *lowered;

    lowered = string_to_lower(original);
    if (lowered == NULL) {
        fprintf(stderr, "Error: conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", original) < 0) {
        free(lowered);
        return EXIT_FAILURE;
    }

    if (printf("Lowered:  %s\n", lowered) < 0) {
        free(lowered);
        return EXIT_FAILURE;
    }

    free(lowered);
    lowered = NULL;

    return EXIT_SUCCESS;
}