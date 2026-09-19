#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got 
  *  test case 2 failed: expected 'alpha', got ��	
  *  test case 1 failed: expected 'string', got @�	
  */

char *remove_parenthesis(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (!result) {
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

    while (j > 0 && result[j - 1] == ' ') {
        j--;
    }

    size_t start = 0;
    while (start < j && result[start] == ' ') {
        start++;
    }

    if (start > 0) {
        memmove(result, result + start, j - start);
        j -= start;
    }

    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk) {
        return shrunk;
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "python",
        "alpha",
        "string",
        "Hello (World) C (Programming) Language"
    };
    
    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        char *output = remove_parenthesis(test_cases[i]);
        if (output) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }
    
    return 0;
}