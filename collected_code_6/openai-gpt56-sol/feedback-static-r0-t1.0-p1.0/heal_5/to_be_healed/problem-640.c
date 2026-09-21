#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_parenthesized(const char *input, size_t length, char **output)
{
    char *result;
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;

    if (input == NULL || output == NULL || length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        switch (input[read_index]) {
        case '(':
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
            break;

        case ')':
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
            break;

        default:
            if (depth == 0) {
                result[write_index++] = input[read_index];
            }
            break;
        }
    }

    if (depth != 0) {
        free(result);
        return -1;
    }

    result[write_index] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    char *input;
    char *output = NULL;
    size_t capacity = 128;
    size_t length = 0;
    int ch = EOF;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == (size_t)MAX_INPUT_LENGTH) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            char *temporary;
            size_t new_capacity;

            if (capacity > ((size_t)MAX_INPUT_LENGTH + 1) / 2) {
                new_capacity = (size_t)MAX_INPUT_LENGTH + 1;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(input);
                return EXIT_FAILURE;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (remove_parenthesized(input, length, &output) != 0) {
        free(input);
        fputs("Invalid input or allocation failure.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}