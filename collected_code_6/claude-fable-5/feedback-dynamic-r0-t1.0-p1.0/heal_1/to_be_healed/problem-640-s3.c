#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got  "S
  *  test case 1 failed: expected 'string', got �!S
  *  test case 0 failed: expected 'python', got �!S
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

    return result;
}

int main(void)
{
    const char *test1 = "Hello (remove me) World";
    const char *test2 = "abc(def(ghi)jkl)mno";
    const char *test3 = "no parentheses here";
    char *output;

    output = remove_parentheses(test1);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (printf("%s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }
    free(output);

    output = remove_parentheses(test2);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (printf("%s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }
    free(output);

    output = remove_parentheses(test3);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (printf("%s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }
    free(output);

    return EXIT_SUCCESS;
}