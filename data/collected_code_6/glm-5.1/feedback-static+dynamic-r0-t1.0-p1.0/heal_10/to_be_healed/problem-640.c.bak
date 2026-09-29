#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got `��
  *  test case 1 failed: expected 'string', got ���
  *  test case 2 failed: expected 'alpha', got ��
  */

char *remove_parenthesis(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    size_t depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else {
            if (depth == 0) {
                result[j++] = str[i];
            }
        }
    }

    result[j] = '\0';

    char *shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *input0 = "python";
    char *output0 = remove_parenthesis(input0);
    if (output0 != NULL) {
        printf("%s\n", output0);
        free(output0);
    }

    const char *input1 = "string";
    char *output1 = remove_parenthesis(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "alpha";
    char *output2 = remove_parenthesis(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    const char *input3 = "Hello (World) this (is a) test!";
    char *output3 = remove_parenthesis(input3);
    if (output3 != NULL) {
        printf("%s\n", output3);
        free(output3);
    }

    const char *input4 = "(Nested (Parentheses)) Outside";
    char *output4 = remove_parenthesis(input4);
    if (output4 != NULL) {
        printf("%s\n", output4);
        free(output4);
    }

    return 0;
}