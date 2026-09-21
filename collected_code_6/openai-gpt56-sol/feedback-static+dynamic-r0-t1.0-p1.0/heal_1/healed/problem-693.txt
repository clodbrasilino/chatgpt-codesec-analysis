#include <stdio.h>
#include <stdlib.h>

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
        if (*read_ptr == ' ') {
            if (!previous_was_space) {
                *write_ptr++ = *read_ptr;
                previous_was_space = 1;
            }
        } else {
            *write_ptr++ = *read_ptr;
            previous_was_space = 0;
        }

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

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                fprintf(stderr, "Input is too large.\n");
                result = EXIT_FAILURE;
                goto cleanup;
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

    if (length + 1 > capacity) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            result = EXIT_FAILURE;
            goto cleanup;
        }

        input = new_input;
        capacity = length + 1;
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