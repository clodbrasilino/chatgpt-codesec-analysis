#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    size_t alloc_size = len + 1;

    char *result = (char *)malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalnum((unsigned char)input[i])) {
            if (j >= alloc_size - 1) {
                free(result);
                return NULL;
            }
            result[j++] = input[i];
        }
    }

    result[j] = '\0';

    char *shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "Hello, World! 123",
        "C@de#2024$",
        "   Spaces   ",
        "NoSpecialChars123",
        "",
        "!@#$%^&*()",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *cleaned = remove_non_alphanumeric(test_cases[i]);
        if (cleaned != NULL) {
            printf("Input: \"%s\" -> Output: \"%s\"\n", test_cases[i], cleaned);
            free(cleaned);
        } else {
            printf("Failed to process: \"%s\"\n", test_cases[i]);
        }
    }

    return 0;
}