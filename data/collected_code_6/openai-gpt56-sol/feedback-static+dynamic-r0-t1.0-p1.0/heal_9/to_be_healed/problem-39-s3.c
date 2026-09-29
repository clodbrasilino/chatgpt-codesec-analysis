#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 256;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fputs("Input is too long.\n", stderr);
                    free(input);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*input)) {
                fputs("Input is too long.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            unsigned char *new_input =
                realloc(input, new_capacity * sizeof(*input));

            if (new_input == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        fputs("Input error.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return EXIT_SUCCESS;
}