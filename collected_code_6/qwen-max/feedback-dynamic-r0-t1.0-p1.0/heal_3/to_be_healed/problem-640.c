#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got �4�
  *  test case 2 failed: expected 'alpha', got 
  *  test case 0 failed: expected 'python', got �4�
  */

char* remove_parentheses(const char *input) {
    int input_len = strlen(input);
    int result_len = 0;
    for (int i = 0; i < input_len; ++i) {
        if (input[i] != '(' && input[i] != ')') {
            result_len++;
        }
    }
    char *result = (char *)malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }
    int result_index = 0;
    int depth = 0;

    for (int i = 0; i < input_len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[result_index++] = input[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char *test_cases[] = {"(python)", "alpha(beta)", "(string)"};
    const char *expected_results[] = {"", "alpha", "string"};

    for (int i = 0; i < 3; ++i) {
        char *output = remove_parentheses(test_cases[i]);
        if (output != NULL) {
            if (strcmp(output, expected_results[i]) == 0) {
                printf("Test case %d passed: got '%s'\n", i, output);
            } else {
                printf("Test case %d failed: expected '%s', got '%s'\n", i, expected_results[i], output);
            }
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }

    return 0;
}