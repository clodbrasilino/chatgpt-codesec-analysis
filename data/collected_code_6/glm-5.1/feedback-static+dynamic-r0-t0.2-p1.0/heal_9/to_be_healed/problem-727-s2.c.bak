#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t result_size = input_len + 1;
    char *result = malloc(result_size);
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

    char *trimmed_result = realloc(result, result_idx + 1);
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    return result;
}

int main(void) {
    char *result1 = remove_non_alnum("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alnum("___test___");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alnum("");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *already_freed = remove_non_alnum("Test");
    if (already_freed != NULL) {
        printf("%s\n", already_freed);
        free(already_freed);
    }

    /* Possible weaknesses found:
     *  Calling function 'remove_non_alnum' returns 0
     *  Assignment 'result4=remove_non_alnum(NULL)', assigned value is 0
     */
    char *result4 = remove_non_alnum(NULL);
    /* Possible weaknesses found:
     *  Condition 'result4!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'result4!=NULL' is always false
     */
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    } else {
        printf("(null)\n");
    }

    return 0;
}