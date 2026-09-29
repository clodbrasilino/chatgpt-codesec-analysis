#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char* remove_whitespace(const char* input, size_t input_len) {
    if (input == NULL) {
        return NULL;
    }

    if (input_len == SIZE_MAX) {
        return NULL;
    }

    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_idx = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n' &&
            input[i] != '\v' && input[i] != '\f' && input[i] != '\r') {
            result[result_idx++] = input[i];
        }
    }

    result[result_idx] = '\0';
    return result;
}

int main(void) {
    const char test_string[] = "Hello World \t This is a test \n string";
    size_t test_len = sizeof(test_string) - 1;
    char* cleaned = remove_whitespace(test_string, test_len);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}