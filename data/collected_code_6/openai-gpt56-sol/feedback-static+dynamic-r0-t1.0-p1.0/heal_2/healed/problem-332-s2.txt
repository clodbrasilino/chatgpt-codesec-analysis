#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    uintmax_t *frequency,
    size_t frequency_length)
{
    if (data == NULL || frequency == NULL ||
        frequency_length < (size_t)UCHAR_MAX + 1U) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t index = data[i];

        if (frequency[index] == UINTMAX_MAX) {
            return -1;
        }

        ++frequency[index];
    }

    return 0;
}

int main(void)
{
    enum { INPUT_SIZE = 4096 };
    unsigned char input[INPUT_SIZE];
    uintmax_t frequency[(size_t)UCHAR_MAX + 1U] = {0};

    for (;;) {
        size_t bytes_read = fread(input, sizeof input[0], sizeof input, stdin);

        if (bytes_read > 0 &&
            count_character_frequency(
                input,
                bytes_read,
                frequency,
                sizeof frequency / sizeof frequency[0]) != 0) {
            fputs("Frequency counter overflow or invalid input.\n", stderr);
            return 1;
        }

        if (bytes_read < sizeof input) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            if (feof(stdin)) {
                break;
            }
        }
    }

    for (size_t i = 0; i < sizeof frequency / sizeof frequency[0]; ++i) {
        if (frequency[i] != 0) {
            printf("0x%02zX: %ju\n", i, frequency[i]);
        }
    }

    return 0;
}