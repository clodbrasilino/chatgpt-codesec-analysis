#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        char *empty = malloc(1);
        if (empty) {
            empty[0] = '\0';
        }
        return empty;
    }

    const char *end = memchr(str, '\0', len);
    size_t actual_len = end ? (size_t)(end - str) : len;

    char *result = malloc(actual_len + 1);
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    size_t depth = 0;

    for (size_t i = 0; i < actual_len; i++) {
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
    const char *inputs[] = {"python", "string", "alpha"};
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t k = 0; k < num_inputs; k++) {
        size_t len = strlen(inputs[k]);
        char *output = remove_parenthesis(inputs[k], len + 1);
        if (output) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}