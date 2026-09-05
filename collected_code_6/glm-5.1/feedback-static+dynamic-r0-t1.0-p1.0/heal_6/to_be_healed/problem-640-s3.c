#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got ���
  *  test case 0 failed: expected 'python', got ���
  *  test case 2 failed: expected 'alpha', got 
  */

char *remove_parenthesis(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len + 1);
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
        } else {
            if (depth == 0) {
                result[j++] = str[i];
            }
        }
    }

    result[j] = '\0';
    
    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "python",
        "string",
        "alpha",
        "Hello (World) this is (a test)"
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        char *output = remove_parenthesis(test_cases[i]);
        if (output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}