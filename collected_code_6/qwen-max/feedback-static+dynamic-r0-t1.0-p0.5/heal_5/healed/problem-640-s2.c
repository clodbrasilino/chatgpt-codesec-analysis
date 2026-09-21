#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis_area(const char *str) {
    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return NULL;
    size_t result_index = 0;
    int depth = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[result_index++] = str[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char input[] = "python (alpha (beta))";
    char *output = remove_parenthesis_area(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}