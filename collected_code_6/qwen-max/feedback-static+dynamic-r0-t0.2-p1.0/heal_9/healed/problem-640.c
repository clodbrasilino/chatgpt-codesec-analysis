#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis_area(const char *input) {
    size_t len = strlen(input);
    if (len == 0) return strdup("");

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    int result_index = 0;
    int depth = 0;

    for (size_t i = 0; i < len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[result_index++] = input[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char *test_cases[] = {
        "(python)",
        "((string))",
        "alpha(beta)"
    };
    const char *expected_outputs[] = {
        "",
        "",
        "alpha"
    };

    for (int i = 0; i < 3; ++i) {
        char *output = remove_parenthesis_area(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            if (strcmp(output, expected_outputs[i]) != 0) {
                fprintf(stderr, "Test case %d failed: expected '%s', got '%s'\n", i, expected_outputs[i], output);
            }
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }

    return 0;
}