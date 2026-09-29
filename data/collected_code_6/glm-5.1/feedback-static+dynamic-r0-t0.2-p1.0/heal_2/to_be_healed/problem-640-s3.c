#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got 
  *  test case 1 failed: expected 'string', got �1�
  *  test case 0 failed: expected 'python', got �1�
  */

char *remove_parenthesis(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    const char *p = str;
    while (*p != '\0') {
        p++;
    }
    size_t len = p - str;

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
    const char *input = "Hello (World) C (Programming) Language";
    char *output = remove_parenthesis(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}