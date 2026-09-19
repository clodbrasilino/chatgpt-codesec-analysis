#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis(const char *input) {
    int len = strlen(input);
    char *output = (char *)malloc(len + 1);
    if (!output) return NULL;
    int j = 0;
    int depth = 0;
    for (int i = 0; i < len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            depth--;
        } else if (depth == 0) {
            if (input[i] != ' ' || (j > 0 && output[j-1] != ' ')) {
                output[j++] = input[i];
            }
        }
    }
    output[j] = '\0';
    return output;
}

int main() {
    const char *test0 = "python( )";
    const char *test1 = "(string)";
    const char *test2 = "(alpha)";
    const char *input = "Hello, (this is a test) and this should stay.";

    char *result0 = remove_parenthesis(test0);
    char *result1 = remove_parenthesis(test1);
    char *result2 = remove_parenthesis(test2);
    char *result = remove_parenthesis(input);

    if (result0) {
        printf("%s\n", result0);
        free(result0);
    }
    if (result1) {
        printf("%s\n", result1);
        free(result1);
    }
    if (result2) {
        printf("%s\n", result2);
        free(result2);
    }
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}