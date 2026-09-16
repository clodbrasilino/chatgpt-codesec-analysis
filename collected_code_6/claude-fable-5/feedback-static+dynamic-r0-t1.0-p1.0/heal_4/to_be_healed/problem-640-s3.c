#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got @b
  *  test case 0 failed: expected 'python', got 
  *  test case 2 failed: expected 'alpha', got �b
  */

char *remove_parentheses(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    int depth;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    result = calloc(len + 1, sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    depth = 0;
    j = 0;
    for (i = 0; i < len; i++) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *tests[] = {
        "python(java)",
        "string(remove)",
        "alpha(beta(gamma)delta)",
        "Hello (remove me) World",
        "abc(def(ghi)jkl)mno",
        "no parentheses here"
    };
    size_t num_tests;
    size_t i;

    num_tests = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < num_tests; i++) {
        char *output = remove_parentheses(tests[i]);
        if (output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        if (printf("%s\n", output) < 0) {
            free(output);
            return EXIT_FAILURE;
        }
        free(output);
    }

    return EXIT_SUCCESS;
}