#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_parenthesized(const char *input, size_t input_length, char **output)
{
    char *result;
    size_t write_index = 0;
    size_t depth = 0;

    if (input == NULL || output == NULL || input_length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t read_index = 0; read_index < input_length; ++read_index) {
        unsigned char current = (unsigned char)input[read_index];

        if (current == (unsigned char)'(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (current == (unsigned char)')') {
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
        } else if (depth == 0) {
            result[write_index++] = (char)current;
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
    enum { INITIAL_CAPACITY = 128 };
    char *input = NULL;
    char *output = NULL;
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    int status = EXIT_FAILURE;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

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

        input[length++] = (char)(unsigned char)ch;
    }

    if (remove_parenthesized(input, length, &output) != 0) {
        fputs("Invalid input or allocation failure.\n", stderr);
        goto cleanup;
    }

    if (fputs(output, stdout) == EOF || fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}