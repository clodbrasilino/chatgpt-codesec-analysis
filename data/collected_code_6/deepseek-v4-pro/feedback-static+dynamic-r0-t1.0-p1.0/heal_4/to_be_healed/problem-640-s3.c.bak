#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got �B�
  *  test case 1 failed: expected 'string', got �B�
  *  test case 2 failed: expected 'alpha', got  C�
  */

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
            } else {
                result[j++] = str[i];
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

    return result;
}

int main(void) {
    const char *test1 = "Hello (this is a test) World";
    const char *test2 = "No parentheses here";
    const char *test3 = "Nested ((parentheses) test) example";
    const char *test4 = "Unmatched (parenthesis";
    const char *test5 = "Multiple (first) and (second) removal";

    char *result = NULL;

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

    /* Possible weaknesses found:
     *  Calling function 'remove_parenthesis_area' returns 0
     *  Assignment 'result=remove_parenthesis_area(NULL)', assigned value is 0
     */
    result = remove_parenthesis_area(NULL);
    /* Possible weaknesses found:
     *  Condition 'result==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result==NULL' is always true
     */
    if (result == NULL) {
        printf("NULL input handled\n");
    } else {
        free(result);
    }

    return 0;
}