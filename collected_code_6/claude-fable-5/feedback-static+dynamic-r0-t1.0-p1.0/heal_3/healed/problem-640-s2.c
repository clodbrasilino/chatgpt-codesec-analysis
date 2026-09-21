#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

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

    len = 0;
    while (len < MAX_INPUT_LEN && input[len] != '\0') {
        len++;
    }

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
        result[j] = '\0';
    }

    return result;
}

int main(void)
{
    const char *tests[] = {
        "py(remove me)thon",
        "str(nested (inner) text)ing",
        "al(unwanted)pha"
    };
    const char *expected[] = {
        "python",
        "string",
        "alpha"
    };
    size_t i;
    size_t count;
    int status;

    count = sizeof(tests) / sizeof(tests[0]);
    status = EXIT_SUCCESS;

    for (i = 0; i < count; i++) {
        char *output = remove_parentheses(tests[i]);
        if (output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        if (strcmp(output, expected[i]) != 0) {
            fprintf(stderr, "test case %zu failed: expected '%s', got '%s'\n",
                    i, expected[i], output);
            status = EXIT_FAILURE;
        } else {
            printf("%s\n", output);
        }
        free(output);
    }

    return status;
}