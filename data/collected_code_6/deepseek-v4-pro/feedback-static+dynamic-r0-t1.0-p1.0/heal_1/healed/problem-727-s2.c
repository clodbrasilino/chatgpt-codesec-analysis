#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_alphanumeric(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    size_t alnum_count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (is_alphanumeric(input[i])) {
            alnum_count++;
        }
    }

    char *result = (char *)malloc(alnum_count + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (is_alphanumeric(input[i])) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

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