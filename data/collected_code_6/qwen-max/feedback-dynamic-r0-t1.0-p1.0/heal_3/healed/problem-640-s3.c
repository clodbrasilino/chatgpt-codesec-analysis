#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis(const char *input) {
    int len = strlen(input);
    int depth = 0;
    int new_len = 0;

    for (int i = 0; i < len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            depth--;
        } else if (depth == 0) {
            new_len++;
        }
    }

    char *output = (char *)malloc(new_len + 1);
    if (!output) return NULL;

    int j = 0;
    depth = 0;
    for (int i = 0; i < len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            depth--;
        } else if (depth == 0) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

int main() {
    const char *inputs[] = {"python", "string", "alpha"};
    const char *expected_outputs[] = {"python", "string", "alpha"};

    for (int k = 0; k < 3; ++k) {
        char *result = remove_parenthesis(inputs[k]);
        if (result) {
            printf("Test case %d: expected '%s', got '%s'\n", k, expected_outputs[k], result);
            free(result);
        } else {
            printf("Test case %d: memory allocation failed\n", k);
        }
    }
    const char *input = "Hello, (this is a test) and this should stay.";
    char *result = remove_parenthesis(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}