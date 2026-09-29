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
        unsigned char character = (unsigned char)input[read_index];

        if (character == '(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (character == ')') {
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
        } else if (depth == 0) {
            result[write_index++] = (char)character;
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
    size_t capacity = 0;
    size_t length = 0;
    int status = EXIT_FAILURE;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        size_t required;

        if (length > SIZE_MAX - 2) {
            goto cleanup;
        }

        required = length + 2;

        if (capacity < required) {
            size_t new_capacity = capacity;
            char *resized;

            if (new_capacity == 0) {
                new_capacity = INITIAL_CAPACITY;
            }

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            goto cleanup;
        }
        capacity = 1;
    }

    input[length] = '\0';

    if (remove_parenthesized(input, length, &output) != 0) {
        fputs("Invalid input\n", stderr);
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