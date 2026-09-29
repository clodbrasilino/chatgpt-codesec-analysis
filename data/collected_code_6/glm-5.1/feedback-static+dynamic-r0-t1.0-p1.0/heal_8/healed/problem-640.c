#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return NULL;
    }

    size_t len = strlen(str);

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
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
    const char *input1 = "python";
    char *output1 = remove_parenthesis(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "string";
    char *output2 = remove_parenthesis(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    const char *input3 = "alpha";
    char *output3 = remove_parenthesis(input3);
    if (output3 != NULL) {
        printf("%s\n", output3);
        free(output3);
    }

    const char *input4 = "Hello (World) this (is a) test!";
    char *output4 = remove_parenthesis(input4);
    if (output4 != NULL) {
        printf("%s\n", output4);
        free(output4);
    }

    const char *input5 = "(Nested (Parentheses)) Outside";
    char *output5 = remove_parenthesis(input5);
    if (output5 != NULL) {
        printf("%s\n", output5);
        free(output5);
    }

    return 0;
}