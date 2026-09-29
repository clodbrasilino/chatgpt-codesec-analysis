#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t max_len = 0;
    while (input[max_len] != '\0') {
        max_len++;
    }
    size_t input_len = max_len;

    size_t result_len = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isalnum((unsigned char)input[i])) {
            result_len++;
        }
    }

    char *result = malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_idx = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isalnum((unsigned char)input[i])) {
            result[result_idx++] = input[i];
        }
    }
    
    result[result_idx] = '\0';

    return result;
}

int main(void) {
    char *result1 = remove_non_alphanumeric("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alphanumeric("Another@test*string");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alphanumeric(NULL);
    if (result3 == NULL) {
        printf("Memory allocation failed\n");
    } else {
        printf("Handled NULL input safely\n");
        free(result3);
    }

    return 0;
}