#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis_area(const char *input) {
    int len = strlen(input);
    int result_len = 0;
    int depth = 0;

    for (int i = 0; i < len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            depth--;
        } else if (depth == 0) {
            result_len++;
        }
    }

    char *result = (char *)malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    int result_index = 0;
    depth = 0;

    for (int i = 0; i < len; ++i) {
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
    const char *test_cases[] = {"python", "string", "alpha"};
    const char *expected[] = {"python", "string", "alpha"};

    for (int i = 0; i < 3; i++) {
        char *output = remove_parenthesis_area(test_cases[i]);
        if (output != NULL) {
            if (strcmp(output, expected[i]) == 0) {
                printf("Test case %d passed: %s\n", i, output);
            } else {
                printf("Test case %d failed: expected '%s', got '%s'\n", i, expected[i], output);
            }
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed.\n");
        }
    }

    const char *input = "This is a (test) string with (multiple) (parentheses).";
    char *output = remove_parenthesis_area(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}