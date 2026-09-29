#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return (const char *)0;
    }

    size_t input_len = strlen(input);
    char *result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_idx = 0;
    for (size_t i = 0; i < input_len; i++) {
        if ((input[i] >= 'a' && input[i] <= 'z') ||
            (input[i] >= 'A' && input[i] <= 'Z') ||
            (input[i] >= '0' && input[i] <= '9')) {
            result[result_idx++] = input[i];
        }
    }

    result[result_idx] = '\0';

    char *final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        final_result = result;
    }

    return final_result;
}

int main(void) {
    const char *result1 = remove_non_alphanumeric("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free((void *)result1);
    }

    const char *result2 = remove_non_alphanumeric("Another@test*string");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free((void *)result2);
    }

    const char *result3 = remove_non_alphanumeric(NULL);
    if (result3 == NULL) {
        printf("Handled NULL input safely\n");
    }

    return 0;
}