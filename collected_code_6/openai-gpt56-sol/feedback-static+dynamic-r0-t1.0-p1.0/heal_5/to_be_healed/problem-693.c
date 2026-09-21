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
    int result = EXIT_SUCCESS;
    int character;

    for (;;) {
        char *new_input;
        size_t new_capacity;
        size_t required;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            fputs("Input is too large.\n", stderr);
            result = EXIT_FAILURE;
            goto cleanup;
        }

        required = length + 2;

        if (required > capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = SIZE_MAX;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                result = EXIT_FAILURE;
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        result = EXIT_FAILURE;
        goto cleanup;
    }

    if (character == EOF && length == 0) {
        goto cleanup;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            result = EXIT_FAILURE;
            goto cleanup;
        }
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = 1;
    }

    input[length] = '\0';

    if (remove_multiple_spaces(input) != 0) {
        fputs("Failed to process input.\n", stderr);
        result = EXIT_FAILURE;
        goto cleanup;
    }

    if (puts(input) == EOF) {
        fputs("Failed to write output.\n", stderr);
        result = EXIT_FAILURE;
    }

cleanup:
    free(input);
    return result;
}