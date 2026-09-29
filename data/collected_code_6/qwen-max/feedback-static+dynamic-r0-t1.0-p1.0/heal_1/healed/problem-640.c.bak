#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_parentheses(const char *input) {
    int input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }
    int result_index = 0;
    int depth = 0;

    for (int i = 0; i < input_len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            depth--;
        } else if (depth == 0) {
            result[result_index++] = input[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char *test_cases[] = {
        "python",
        "(ignore this) string",
        "(alpha(beta))",
        "This is a (test string) with (multiple) parentheses."
    };

    for (int i = 0; i < 4; ++i) {
        char *output = remove_parentheses(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }
    return 0;
}