#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_parentheses(const char *input, char *output, size_t output_size)
{
    size_t i;
    size_t j;
    int depth;
    size_t len;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    len = strlen(input);
    j = 0;
    depth = 0;

    for (i = 0; i < len; i++) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            if (j + 1 >= output_size) {
                output[j] = '\0';
                return -1;
            }
            output[j] = input[i];
            j++;
        }
    }

    output[j] = '\0';

    if (depth != 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *test_strings[] = {
        "Hello (world) example",
        "No parentheses here",
        "(remove this) keep this",
        "Nested (outer (inner) more) text",
        "Multiple (one) and (two) groups"
    };
    size_t count;
    size_t i;

    count = sizeof(test_strings) / sizeof(test_strings[0]);

    for (i = 0; i < count; i++) {
        size_t buf_size = strlen(test_strings[i]) + 1;
        char *buffer = (char *)malloc(buf_size);

        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        if (remove_parentheses(test_strings[i], buffer, buf_size) == 0) {
            printf("Input:  \"%s\"\n", test_strings[i]);
            printf("Output: \"%s\"\n\n", buffer);
        } else {
            fprintf(stderr, "Failed to process: \"%s\"\n", test_strings[i]);
        }

        free(buffer);
        buffer = NULL;
    }

    return EXIT_SUCCESS;
}