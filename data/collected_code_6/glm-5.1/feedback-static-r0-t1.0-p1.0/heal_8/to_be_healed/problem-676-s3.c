#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return malloc(1);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    
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