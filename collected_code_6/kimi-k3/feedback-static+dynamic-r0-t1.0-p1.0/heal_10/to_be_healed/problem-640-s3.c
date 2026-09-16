#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got <no output>
  *  test case 1 failed: expected 'string', got <no output>
  *  test case 2 failed: expected 'alpha', got <no output>
  */

char *remove_parenthesis_area(const char *str)
{
    char *result;
    size_t len;
    size_t i;
    size_t j;
    int depth;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    depth = 0;

    for (i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j] = str[i];
            j++;
        }
    }

    result[j] = '\0';
    return result;
}

int main(void)
{
    const char *inputs[] = {
        "(remove this)python(also remove)",
        "string(with parens)",
        "alpha(beta)gamma(delta)"
    };
    const char *expected[] = {
        "python",
        "string",
        "alpha"
    };
    size_t num_tests = sizeof(inputs) / sizeof(inputs[0]);
    size_t i;
    int all_passed = 1;

    for (i = 0; i < num_tests; i++) {
        char *output = remove_parenthesis_area(inputs[i]);
        if (output == NULL) {
            fprintf(stderr, "Error: Memory allocation failed or invalid input\n");
            return EXIT_FAILURE;
        }

        if (strcmp(output, expected[i]) == 0) {
            printf("Test %zu: PASS - got '%s'\n", i, output);
        } else {
            printf("Test %zu: FAIL - expected '%s', got '%s'\n", i, expected[i], output);
            all_passed = 0;
        }

        free(output);
        output = NULL;
    }

    return all_passed ? EXIT_SUCCESS : EXIT_FAILURE;
}