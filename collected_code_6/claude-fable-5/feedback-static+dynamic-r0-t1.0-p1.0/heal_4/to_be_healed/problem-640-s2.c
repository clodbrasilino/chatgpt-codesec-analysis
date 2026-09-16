#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got ��
  *  test case 1 failed: expected 'string', got ���
  *  test case 0 failed: expected 'python', got `��
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
        "py(remove me)thon",
        "str(outer (inner) text)ing",
        "alpha"
    };
    const char *expected[] = {
        "python",
        "string",
        "alpha"
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
        if (strcmp(output, expected[i]) != 0) {
            fprintf(stderr, "test case %zu failed: expected '%s', got '%s'\n",
                    i, expected[i], output);
            free(output);
            return EXIT_FAILURE;
        }
        printf("%s\n", output);
        free(output);
    }

    return EXIT_SUCCESS;
}