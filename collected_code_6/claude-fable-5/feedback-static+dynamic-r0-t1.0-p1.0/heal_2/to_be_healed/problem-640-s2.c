#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got ���
  *  test case 1 failed: expected 'string', got ���
  *  test case 0 failed: expected 'python', got `��
  */

char *remove_parentheses(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    int depth;
    char *result;
    char *shrunk;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);

    result = malloc(len + 1);
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

    shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void)
{
    const char *tests[] = {
        "Hello (remove me) World",
        "Nested (outer (inner) text) example",
        "No parentheses here"
    };
    size_t i;
    size_t count;
    /* Possible weaknesses found:
     *  The scope of the variable 'output' can be reduced. [variableScope]
     */
    char *output;

    count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < count; i++) {
        output = remove_parentheses(tests[i]);
        if (output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        printf("%s\n", output);
        free(output);
        output = NULL;
    }

    return EXIT_SUCCESS;
}