#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got  s�	
  *  test case 1 failed: expected 'string', got `s�	
  *  test case 2 failed: expected 'alpha', got �s�	
  */

char *remove_parenthesis(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

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

    while (depth > 0) {
        result[j++] = '(';
        depth--;
    }

    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *inputs[] = {
        "python",
        "string",
        "alpha",
        "Hello (World) C (Programming) Language",
        "Unmatched ) parenthesis ("
    };

    for (size_t k = 0; k < sizeof(inputs) / sizeof(inputs[0]); k++) {
        char *output = remove_parenthesis(inputs[k]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}