#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

    size_t actual_len = strnlen(str, len);
    if (actual_len == len && str[len] != '\0') {
        return NULL;
    }

    char *result = malloc(actual_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

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
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *input1 = "Hello (World) this (is a) test!";
    size_t len1 = strlen(input1);
    char *output1 = remove_parenthesis(input1, len1);

    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "(Nested (Parentheses)) Outside";
    size_t len2 = strlen(input2);
    char *output2 = remove_parenthesis(input2, len2);

    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    return 0;
}