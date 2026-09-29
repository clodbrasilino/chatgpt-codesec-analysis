#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got �a�
  *  test case 1 failed: expected 'string', got �a�
  *  test case 0 failed: expected 'python', got @a�
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

static int run_test(const char *input)
{
    char *output;

    output = remove_parentheses(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    if (printf("%s\n", output) < 0) {
        free(output);
        return -1;
    }
    free(output);
    return 0;
}

int main(void)
{
    const char *test1 = "Hello (remove me) World";
    const char *test2 = "abc(def(ghi)jkl)mno";
    const char *test3 = "no parentheses here";

    if (run_test(test1) != 0) {
        return EXIT_FAILURE;
    }
    if (run_test(test2) != 0) {
        return EXIT_FAILURE;
    }
    if (run_test(test3) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}