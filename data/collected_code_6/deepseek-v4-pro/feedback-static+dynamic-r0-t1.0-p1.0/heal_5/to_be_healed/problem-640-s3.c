#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got <no output>
  *  test case 2 failed: expected 'alpha', got <no output>
  *  test case 0 failed: expected 'python', got <no output>
  */

char *remove_parenthesis_area(const char *str) {
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
    const char *test0 = "python";
    const char *test1 = "string";
    const char *test2 = "alpha";
    const char *test3 = "Hello (this is a test) World";
    const char *test4 = "No parentheses here";
    const char *test5 = "Nested ((parentheses) test) example";
    const char *test6 = "Unmatched (parenthesis";
    const char *test7 = "Multiple (first) and (second) removal";
    const char *null_test = NULL;

    char *result = NULL;

    result = remove_parenthesis_area(test0);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_parenthesis_area(test1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_parenthesis_area(test2);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_parenthesis_area(test3);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_parenthesis_area(test4);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_parenthesis_area(test5);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_parenthesis_area(test6);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_parenthesis_area(test7);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    /* Possible weaknesses found:
     *  Calling function 'remove_parenthesis_area' returns 0
     *  Assignment 'result=remove_parenthesis_area(null_test)', assigned value is 0
     */
    result = remove_parenthesis_area(null_test);
    /* Possible weaknesses found:
     *  Condition 'result==NULL' is always true
     *  Condition 'result==NULL' is always true [knownConditionTrueFalse]
     */
    if (result == NULL) {
        printf("NULL input handled\n");
    } else {
        free(result);
    }

    return 0;
}