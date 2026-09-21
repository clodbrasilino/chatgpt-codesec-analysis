#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_swap(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            result[i] = '_';
        } else if (str[i] == '_') {
            result[i] = ' ';
        } else {
            result[i] = str[i];
        }
    }

    result[len] = '\0';

    return result;
}

int main(void) {
    char *result1 = replace_whitespace_swap("hello world_this_is_a_test");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = replace_whitespace_swap("no_spaces_or_underscores");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    /* Possible weaknesses found:
     *  Calling function 'replace_whitespace_swap' returns 0
     *  Assignment 'result3=replace_whitespace_swap(NULL)', assigned value is 0
     */
    char *result3 = replace_whitespace_swap(NULL);

    /* Possible weaknesses found:
     *  Condition 'result3==NULL' is always true
     *  Condition 'result3==NULL' is always true [knownConditionTrueFalse]
     */
    if (result3 == NULL) {
        printf("Handled NULL input correctly\n");
    } else {
        free(result3);
    }

    return 0;
}