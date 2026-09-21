#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_parenthesized(const char *input, size_t input_length, char **output)
{
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;
    char *result;

    if (input == NULL || output == NULL || input_length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < input_length; ++read_index) {
        if (input[read_index] == '(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (input[read_index] == ')') {
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
        } else if (depth == 0) {
            result[write_index++] = input[read_index];
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
    char *input = NULL;
    char *output = NULL;
    size_t capacity = 128;
    size_t length = 0;
    int ch;
    int status = EXIT_FAILURE;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                goto cleanup;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        goto cleanup;
    }

    if (remove_parenthesized(input, length, &output) != 0) {
        fputs("Invalid input or allocation failure.\n", stderr);
        goto cleanup;
    }

    if (puts(output) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}