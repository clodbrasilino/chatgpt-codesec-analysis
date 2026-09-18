#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parentheses(const char *input);
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got <no output>
  *  test case 0 failed: expected 'python', got <no output>
  *  test case 1 failed: expected 'string', got <no output>
  */

char *remove_parentheses(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *output = (char *)malloc(len + 1);
    
    if (output == NULL) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            output[j++] = input[i];
        }
    }
    
    output[j] = '\0';

    char *resized_output = (char *)realloc(output, j + 1);
    if (resized_output != NULL) {
        return resized_output;
    }

    return output;
}

int main(void) {
    const char *test_string = "Hello (this is a test) World!";
    char *result = remove_parentheses(test_string);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}