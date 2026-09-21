#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    
    size_t result_len = 0;
    for (size_t i = 0; i < input_len; i++) {
        if ((input[i] >= 'a' && input[i] <= 'z') ||
            (input[i] >= 'A' && input[i] <= 'Z') ||
            (input[i] >= '0' && input[i] <= '9')) {
            result_len++;
        }
    }

    char *result = malloc(result_len + 1);
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

    /* Possible weaknesses found:
     *  Calling function 'remove_non_alphanumeric' returns 0
     *  Assignment 'result3=remove_non_alphanumeric(NULL)', assigned value is 0
     */
    char *result3 = remove_non_alphanumeric(NULL);
    /* Possible weaknesses found:
     *  Condition 'result3==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result3==NULL' is always true
     */
    if (result3 == NULL) {
        printf("Handled NULL input safely\n");
    } else {
        free(result3);
    }

    return 0;
}