#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

static bool can_rearrange_without_adjacent_duplicates(
    const unsigned char *data,
    size_t length)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_frequency = 0;

    if (data == NULL && length != 0) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = ++frequencies[data[i]];

        if (frequency > max_frequency) {
            max_frequency = frequency;
        }
    }

    return max_frequency <= length / 2 + length % 2;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int status = EXIT_SUCCESS;
    int character;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 256;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fputs("Input is too long.\n", stderr);
                    status = EXIT_FAILURE;
                    goto cleanup;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                fputs("Input is too long.\n", stderr);
                status = EXIT_FAILURE;
                goto cleanup;
            }

            unsigned char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                status = EXIT_FAILURE;
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        fputs("Input error.\n", stderr);
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (length != 0 && input[length - 1] == '\r') {
        --length;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

cleanup:
    free(input);
    return status;
}