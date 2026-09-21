#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 4096 };

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

    return max_frequency <= (length / 2U) + (length % 2U);
}

int main(void)
{
    unsigned char input[INPUT_CAPACITY];
    size_t length = 0;
    bool too_long = false;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (length < sizeof input) {
            input[length++] = (unsigned char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (too_long) {
        fputs("Input is too long.\n", stderr);
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    return 0;
}