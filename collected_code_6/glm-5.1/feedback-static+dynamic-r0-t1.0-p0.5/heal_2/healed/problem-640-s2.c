#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis(const char *str, size_t len) {
    char *result = malloc(len + 1);
    if (!result) {
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

    for (size_t i = 0; i < j; i++) {
        if (result[i] == ' ') {
            size_t k = i + 1;
            while (k < j && result[k] == ' ') {
                k++;
            }
            if (k > i + 1) {
                memmove(&result[i + 1], &result[k], j - k + 1);
                j -= (k - (i + 1));
            }
        }
    }

    if (j > 0) {
        if (result[0] == ' ') {
            memmove(result, result + 1, j);
            j--;
        }
        if (j > 0 && result[j - 1] == ' ') {
            result[j - 1] = '\0';
            j--;
        }
    }

    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *input = "Hello (World) C (Programming) Language";
    size_t len = strnlen(input, 1024);
    char *output = remove_parenthesis(input, len);
    
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    return 0;
}