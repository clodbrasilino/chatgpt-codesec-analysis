#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    const char *test2 = "Nested (outer (inner) text) example";
    const char *test3 = "No parentheses here";
    char *output;

    output = remove_parentheses(test1);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", output);
    free(output);

    output = remove_parentheses(test2);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", output);
    free(output);

    output = remove_parentheses(test3);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", output);
    free(output);

    return EXIT_SUCCESS;
}