#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got 
  *  test case 2 failed: expected 'alpha', got @E
  *  test case 0 failed: expected 'python', got �E
  */

char* remove_parentheses(const char *input) {
    int input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }
    int result_index = 0;
    int depth = 0;

    for (int i = 0; i < input_len; ++i) {
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
    const char *input = "This is a (test string) with (multiple) parentheses.";
    char *output = remove_parentheses(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}