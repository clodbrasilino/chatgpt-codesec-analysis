#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INITIAL_CAPACITY 128U

static bool can_rearrange_without_adjacent_duplicates(
    const unsigned char *string,
    size_t length)
{
    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t maximum = 0U;

    if (string == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        size_t frequency = ++frequencies[string[i]];

        if (frequency > maximum) {
            maximum = frequency;
        }
    }

    return maximum <= (length / 2U) + (length % 2U);
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
        int character;

        if (length == capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2U;
            unsigned char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) != 0 || length == 0U) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        input[length++] = (unsigned char)character;
    }

    if (length > 0U && input[length - 1U] == (unsigned char)'\r') {
        --length;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return EXIT_SUCCESS;
}