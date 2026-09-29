#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool can_rearrange_without_adjacent_duplicates(
    const unsigned char *data,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t max_frequency = 0;

    if (data == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = ++frequencies[data[i]];

        if (frequency > max_frequency) {
            max_frequency = frequency;
        }
    }

    return max_frequency <= length / 2U + length % 2U;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 256U : capacity * 2U;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof *input) {
                fputs("Input is too long.\n", stderr);
                free(input);
                return 1;
            }

            unsigned char *new_input = realloc(
                input, new_capacity * sizeof *input);

            if (new_input == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        fputs("Input error.\n", stderr);
        free(input);
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return 0;
}