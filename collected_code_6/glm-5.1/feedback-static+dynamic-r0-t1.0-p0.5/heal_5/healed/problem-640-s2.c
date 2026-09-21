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
                if (j == 0 && str[i] == ' ') {
                    continue;
                }
                if (j > 0 && result[j - 1] == ' ' && str[i] == ' ') {
                    continue;
                }
                result[j++] = str[i];
            }
        }
    }

    if (j > 0 && result[j - 1] == ' ') {
        j--;
    }

    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "python",
        "string",
        "alpha",
        "Hello (World) C (Programming) Language"
    };
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        size_t len = strnlen(test_cases[i], 1024);
        char *output = remove_parenthesis(test_cases[i], len);
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