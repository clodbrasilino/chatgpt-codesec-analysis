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

    return result;
}

static int process_line(const char *input)
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
    char buffer[MAX_INPUT_LEN];
    size_t len;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        if (process_line(buffer) != 0) {
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}