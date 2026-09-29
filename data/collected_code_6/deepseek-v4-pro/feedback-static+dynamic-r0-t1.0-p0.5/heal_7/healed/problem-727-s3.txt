#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    const char *ptr = input;
    while (*ptr != '\0') {
        ptr++;
    }
    size_t input_len = (size_t)(ptr - input);

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    const char *cursor = input;

    while (*cursor != '\0') {
        if ((*cursor >= 'A' && *cursor <= 'Z') ||
            (*cursor >= 'a' && *cursor <= 'z') ||
            (*cursor >= '0' && *cursor <= '9')) {
            result[result_index++] = *cursor;
        }
        cursor++;
    }

    result[result_index] = '\0';
    return result;
}

int main(void) {
    const char *test_string = "Hello, World! 123 @#$%^&*()";
    char *cleaned = remove_non_alphanumeric(test_string);

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