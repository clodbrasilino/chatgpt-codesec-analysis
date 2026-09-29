#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got ��/
  *  test case 1 failed: expected 'string', got ��/
  *  test case 2 failed: expected 'alpha', got  �/
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

    size_t i = 0, j = 0;
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
    const char *test1 = "python";
    const char *test2 = "string";
    const char *test3 = "alpha";

    char *r1 = remove_parenthesis_area(test1);
    char *r2 = remove_parenthesis_area(test2);
    char *r3 = remove_parenthesis_area(test3);
    /* Possible weaknesses found:
     *  Calling function 'remove_parenthesis_area' returns 0
     *  Assignment 'r4=remove_parenthesis_area(NULL)', assigned value is 0
     */
    char *r4 = remove_parenthesis_area(NULL);

    printf("Test 1: %s -> %s\n", test1, r1 ? r1 : "NULL");
    printf("Test 2: %s -> %s\n", test2, r2 ? r2 : "NULL");
    printf("Test 3: %s -> %s\n", test3, r3 ? r3 : "NULL");
    /* Possible weaknesses found:
     *  Condition 'r4' is always false
     *  Condition 'r4' is always false [knownConditionTrueFalse]
     */
    printf("Test 4: NULL -> %s\n", r4 ? r4 : "NULL");

    free(r1);
    free(r2);
    free(r3);
    free(r4);

    return 0;
}