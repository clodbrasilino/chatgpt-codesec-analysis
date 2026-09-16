#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got `�]
  *  test case 2 failed: expected 'alpha', got ��]
  *  test case 1 failed: expected 'string', got ��]
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
    size_t depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
        } else {
            if (depth == 0) {
                result[j++] = str[i];
            }
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
    const char *test0 = "(python)";
    char *mod0 = remove_parenthesis(test0);
    if (mod0 != NULL) {
        printf("%s\n", mod0);
        free(mod0);
    }

    const char *test1 = "(string)";
    char *mod1 = remove_parenthesis(test1);
    if (mod1 != NULL) {
        printf("%s\n", mod1);
        free(mod1);
    }

    const char *test2 = "(alpha)";
    char *mod2 = remove_parenthesis(test2);
    if (mod2 != NULL) {
        printf("%s\n", mod2);
        free(mod2);
    }

    const char *original = "This (is a) test (string)!";
    char *modified = remove_parenthesis(original);
    if (modified != NULL) {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", modified);
        free(modified);
    }

    char *null_test = remove_parenthesis(NULL);
    if (null_test == NULL) {
        printf("NULL input handled successfully.\n");
    }

    return 0;
}