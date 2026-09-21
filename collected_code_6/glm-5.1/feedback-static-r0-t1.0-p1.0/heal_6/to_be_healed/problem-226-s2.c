#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len / 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklmnopqrstuvwxyz";
    char *output = remove_odd_index_chars(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
        output = NULL;
    }

    const char *test_str = "test";
    char *test_output = remove_odd_index_chars(test_str);
    if (test_output != NULL) {
        printf("%s\n", test_output);
        free(test_output);
    }

    /* Possible weaknesses found:
     *  Variable 'null_test' can be declared as pointer to const [constVariablePointer]
     *  Assignment 'null_test=remove_odd_index_chars(NULL)', assigned value is 0
     *  Calling function 'remove_odd_index_chars' returns 0
     */
    char *null_test = remove_odd_index_chars(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_test == NULL) {
        printf("NULL test handled correctly.\n");
    }

    return 0;
}