#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t max_len = strnlen(input, 1024 * 1024);
    char *result = malloc(max_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_idx = 0;
    for (size_t i = 0; i < max_len && input[i] != '\0'; i++) {
        if (isalnum((unsigned char)input[i])) {
            result[result_idx++] = input[i];
        }
    }

    result[result_idx] = '\0';

    if (result_idx == max_len) {
        return result;
    }

    char *final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        return result;
    }

    return final_result;
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
     *  Assignment 'result3=remove_non_alphanumeric(NULL)', assigned value is 0
     *  Calling function 'remove_non_alphanumeric' returns 0
     */
    char *result3 = remove_non_alphanumeric(NULL);
    /* Possible weaknesses found:
     *  Condition 'result3==NULL' is always true
     *  Condition 'result3==NULL' is always true [knownConditionTrueFalse]
     */
    if (result3 == NULL) {
        printf("Handled NULL input safely\n");
    } else {
        free(result3);
    }

    return 0;
}