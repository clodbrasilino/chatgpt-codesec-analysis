#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis_area(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int depth = 0;

    while (i < len) {
        if (str[i] == '(') {
            depth++;
            i++;
            continue;
        }
        if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
            i++;
            continue;
        }
        if (depth == 0) {
            result[j++] = str[i];
        }
        i++;
    }

    result[j] = '\0';

    char *final_result = realloc(result, j + 1);
    if (final_result != NULL) {
        return final_result;
    }

    return result;
}

int main(void) {
    const char *tests[] = {
        "Hello (this is a test) World",
        "No parentheses here",
        "Nested ((parentheses) test) example",
        "Unmatched (parenthesis",
        "Multiple (first) and (second) removal"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t t;

    for (t = 0; t < num_tests; t++) {
        char *result = remove_parenthesis_area(tests[t]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }

    /* Possible weaknesses found:
     *  Calling function 'remove_parenthesis_area' returns 0
     *  Assignment 'null_result=remove_parenthesis_area(NULL)', assigned value is 0
     */
    char *null_result = remove_parenthesis_area(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_result==NULL' is always true
     *  Condition 'null_result==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_result == NULL) {
        printf("NULL input handled\n");
    } else {
        printf("%s\n", null_result);
        free(null_result);
    }

    return 0;
}