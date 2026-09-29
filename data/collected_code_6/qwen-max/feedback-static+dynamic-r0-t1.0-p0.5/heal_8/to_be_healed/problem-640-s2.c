#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got @��
  *  test case 2 failed: expected 'alpha', got ���
  *  test case 1 failed: expected 'string', got ���
  */

char* remove_parenthesis_area(const char *str) {
    if (str == NULL) return NULL;
    size_t len = strnlen(str, 1000);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return NULL;
    size_t result_index = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
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
    const char input1[] = "string (with) parenthesis";
    const char input2[] = "python (alpha (beta))";
    const char input3[] = "alpha (beta (gamma))";

    char *output1 = remove_parenthesis_area(input1);
    char *output2 = remove_parenthesis_area(input2);
    char *output3 = remove_parenthesis_area(input3);

    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    if (output3 != NULL) {
        printf("%s\n", output3);
        free(output3);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}