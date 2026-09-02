#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got ���
  *  test case 0 failed: expected 'python', got  ��
  *  test case 1 failed: expected 'string', got `��
  */

char* remove_parenthesis_area(const char *input) {
    int len = strlen(input);
    int new_len = 0;
    int depth = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            depth--;
        } else if (depth == 0) {
            new_len++;
        }
    }

    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[new_len] = '\0';
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

    return result;
}

int main() {
    const char *test_cases[] = {"python(string)alpha", "example(test)", "sample"};
    const char *expected[] = {"pythonalpha", "example", "sample"};

    for (int i = 0; i < 3; i++) {
        char *output = remove_parenthesis_area(test_cases[i]);
        if (output != NULL) {
            printf("Test case %d: %s\n", i+1, output);
            if (strcmp(output, expected[i]) == 0) {
                printf("Success: Expected '%s', got '%s'\n", expected[i], output);
            } else {
                printf("Failure: Expected '%s', got '%s'\n", expected[i], output);
            }
            free(output);
        } else {
            fprintf(stderr, "Test case %d: Memory allocation failed\n", i+1);
        }
    }

    return 0;
}