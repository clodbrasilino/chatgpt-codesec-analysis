#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got ���
  *  test case 2 failed: expected 'alpha', got  ��
  *  test case 1 failed: expected 'string', got ���
  */

char* remove_parenthesis_area(const char *input) {
    int len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    int depth = 0;
    int j = 0;

    for (int i = 0; i < len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j++] = input[i];
        }
    }

    result[j] = '\0';
    return result;
}

int main() {
    const char *input = "This is a (test string with (nested) parentheses)";
    char *output = remove_parenthesis_area(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}