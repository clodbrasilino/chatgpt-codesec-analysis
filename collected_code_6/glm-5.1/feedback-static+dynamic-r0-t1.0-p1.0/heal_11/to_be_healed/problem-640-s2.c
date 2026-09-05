#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got `�t
  *  test case 1 failed: expected 'string', got ��t
  *  test case 2 failed: expected 'alpha', got ��t
  */

char *remove_parenthesis(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
        } else if (depth == 0) {
            result[j++] = str[i];
        }
    }

    result[j] = '\0';

    char *shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        return shrunk;
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "(python)",
        "(string)",
        "(alpha)",
        "This (is a) test (string)!"
    };
    
    for (int i = 0; i < 4; i++) {
        char *modified = remove_parenthesis(test_cases[i]);
        if (modified != NULL) {
            printf("Original: %s\n", test_cases[i]);
            printf("Modified: %s\n", modified);
            free(modified);
        }
    }

    /* Possible weaknesses found:
     *  Assignment 'null_test=remove_parenthesis(NULL)', assigned value is 0
     *  Calling function 'remove_parenthesis' returns 0
     */
    char *null_test = remove_parenthesis(NULL);

    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'null_test==NULL' is always true
     */
    if (null_test == NULL) {
        printf("NULL input handled successfully.\n");
    } else {
        free(null_test);
    }

    return 0;
}