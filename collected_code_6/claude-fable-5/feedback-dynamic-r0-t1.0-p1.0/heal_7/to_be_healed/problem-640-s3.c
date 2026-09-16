#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got ��{
  *  test case 1 failed: expected 'string', got ��{
  *  test case 0 failed: expected 'python', got `�{
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
            if (depth < INT_MAX) {
                depth++;
            }
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            if (j < len) {
                result[j] = input[i];
                j++;
            }
        }
    }
    result[j] = '\0';

    return result;
}

static int run_test(const char *input, const char *expected)
{
    char *output;
    int status;

    if (input == NULL || expected == NULL) {
        fprintf(stderr, "Invalid test parameters\n");
        return -1;
    }

    output = remove_parentheses(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    status = 0;
    if (strcmp(output, expected) != 0) {
        fprintf(stderr, "Test failed: expected '%s', got '%s'\n",
                expected, output);
        status = -1;
    }

    if (printf("%s\n", output) < 0) {
        status = -1;
    }

    free(output);
    output = NULL;
    return status;
}

int main(void)
{
    const char *test1 = "Hello (remove me) World";
    const char *expected1 = "Hello  World";
    const char *test2 = "abc(def(ghi)jkl)mno";
    const char *expected2 = "abcmno";
    const char *test3 = "no parentheses here";
    const char *expected3 = "no parentheses here";

    if (run_test(test1, expected1) != 0) {
        return EXIT_FAILURE;
    }
    if (run_test(test2, expected2) != 0) {
        return EXIT_FAILURE;
    }
    if (run_test(test3, expected3) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}