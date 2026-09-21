#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 256U

static bool can_rearrange_without_equal_adjacent(
    const unsigned char *data,
    size_t length)
{
    size_t frequencies[UCHAR_MAX + 1U] = {0U};
    size_t max_frequency = 0U;

    if (data == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        size_t index = data[i];

        if (frequencies[index] == SIZE_MAX) {
            return false;
        }

        ++frequencies[index];

        if (frequencies[index] > max_frequency) {
            max_frequency = frequencies[index];
        }
    }

    return max_frequency <= (length / 2U) + (length % 2U);
}

int main(void)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0U;
    unsigned char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= capacity) {
            size_t new_capacity;
            unsigned char *resized_input;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized_input = realloc(input, new_capacity);

            if (resized_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized_input;
            capacity = new_capacity;
        }

        input[length] = (unsigned char)character;
        ++length;
    }

    if (length > 0U && input[length - 1U] == (unsigned char)'\r') {
        --length;
    }

    bool result = can_rearrange_without_equal_adjacent(input, length);

    if (puts(result ? "true" : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}