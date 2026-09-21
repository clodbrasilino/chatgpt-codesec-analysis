#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis_area(const char *input) {
    size_t len = 0;
    const char *ptr = input;
    int depth = 0;

    while (*ptr) {
        if (depth == 0 && *ptr != '(' && *ptr != ')') len++;
        if (*ptr == '(') depth++;
        else if (*ptr == ')') depth--;
        ptr++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) return NULL;

    depth = 0;
    int j = 0;

    for (size_t i = 0; input[i]; ++i) {
        if (input[i] == '(') depth++;
        else if (input[i] == ')') depth--;
        else if (depth == 0) result[j++] = input[i];
    }

    result[j] = '\0';
    return result;
}

int main() {
    const char *test_cases[] = {
        "python",
        "string",
        "alpha",
        "This is a (test string with (nested) parentheses)"
    };
    const int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        char *output = remove_parenthesis_area(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }

    return 0;
}