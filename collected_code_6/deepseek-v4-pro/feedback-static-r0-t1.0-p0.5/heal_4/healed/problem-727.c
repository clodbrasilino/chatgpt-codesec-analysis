#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int is_alphanumeric(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    const char *ptr = input;
    while (*ptr != '\0') {
        input_len++;
        if (input_len >= SIZE_MAX) {
            return NULL;
        }
        ptr++;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (is_alphanumeric((unsigned char)input[i])) {
            result[result_index++] = input[i];
        }
    }
    result[result_index] = '\0';

    char *shrunk = (char *)realloc(result, result_index + 1);
    if (shrunk != NULL) {
        return shrunk;
    }
    return result;
}

int main(void) {
    const char *test_string = "Hello, World! 123";
    char *cleaned = remove_non_alphanumeric(test_string);
    
    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned:  %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}