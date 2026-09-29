#include <stdio.h>
#include <stdlib.h>

char* remove_parenthesis_area(const char *input) {
    size_t len = 0;
    const char *p = input;
    while (*p) {
        if (*p != '(' && *p != ')') {
            len++;
        }
        p++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    int result_index = 0;
    int depth = 0;

    for (int i = 0; input[i]; ++i) {
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
    const char *input = "This is a (test string) with (multiple) parenthesis.";
    char *output = remove_parenthesis_area(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}