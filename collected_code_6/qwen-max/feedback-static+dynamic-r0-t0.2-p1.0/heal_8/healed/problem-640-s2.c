#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis_area(const char *str) {
    int len = strlen(str);
    int new_len = 0;
    int depth = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            depth--;
        } else if (depth == 0) {
            new_len++;
        }
    }

    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) return NULL;

    int result_index = 0;
    depth = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            depth--;
        } else if (depth == 0) {
            result[result_index++] = str[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char input[] = "This is a (test string with (nested) parentheses)";
    char *output = remove_parenthesis_area(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}