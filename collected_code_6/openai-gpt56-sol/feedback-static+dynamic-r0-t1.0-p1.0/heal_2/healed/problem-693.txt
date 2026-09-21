#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int remove_multiple_spaces(char *string)
{
    char *read_ptr;
    char *write_ptr;
    int previous_was_space = 0;

    if (string == NULL) {
        return -1;
    }

    read_ptr = string;
    write_ptr = string;

    while (*read_ptr != '\0') {
        if (*read_ptr != ' ' || !previous_was_space) {
            *write_ptr++ = *read_ptr;
        }

        previous_was_space = (*read_ptr == ' ');
        ++read_ptr;
    }

    *write_ptr = '\0';
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;
    int result = EXIT_SUCCESS;

    for (;;) {
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            fprintf(stderr, "Input is too large.\n");
            result = EXIT_FAILURE;
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fprintf(stderr, "Failed to allocate memory.\n");
                result = EXIT_FAILURE;
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        result = EXIT_FAILURE;
        goto cleanup;
    }

    if (character == EOF && length == 0) {
        goto cleanup;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            result = EXIT_FAILURE;
            goto cleanup;
        }
    }

    input[length] = '\0';

    if (remove_multiple_spaces(input) != 0) {
        fprintf(stderr, "Failed to process input.\n");
        result = EXIT_FAILURE;
        goto cleanup;
    }

    if (puts(input) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        result = EXIT_FAILURE;
    }

cleanup:
    free(input);
    return result;
}