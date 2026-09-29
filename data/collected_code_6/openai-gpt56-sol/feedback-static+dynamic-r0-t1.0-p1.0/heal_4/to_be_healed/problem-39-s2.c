#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 128U

static bool can_rearrange_without_adjacent_duplicates(
    const char *string,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t maximum = 0;

    if (string == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        ++frequencies[character];
        if (frequencies[character] > maximum) {
            maximum = frequencies[character];
        }
    }

    return maximum <= (length / 2U) + (length % 2U);
}

int main(void)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    char *input = malloc(capacity);
    int character;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return EXIT_SUCCESS;
}