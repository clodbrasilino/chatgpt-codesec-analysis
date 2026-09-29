#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < 1024 * 1024 && str[len] != '\0') {
        len++;
    }
    if (str[len] != '\0') {
        return NULL;
    }

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
        "string"
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

    const char *input = "Hello (World) C (Programming) Language";
    char *output = remove_parenthesis(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}