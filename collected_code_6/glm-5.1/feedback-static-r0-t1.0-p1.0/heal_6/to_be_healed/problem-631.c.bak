#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_swap(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == ' ') {
            result[index++] = '_';
        } else if (str[i] == '_') {
            result[index++] = ' ';
        } else {
            result[index++] = str[i];
        }
    }

    result[index] = '\0';

    char *shrunk = realloc(result, index + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

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
     *  Condition 'result3==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result3==NULL' is always true
     */
    if (result3 == NULL) {
        printf("Handled NULL input correctly\n");
    } else {
        free(result3);
    }

    return 0;
}