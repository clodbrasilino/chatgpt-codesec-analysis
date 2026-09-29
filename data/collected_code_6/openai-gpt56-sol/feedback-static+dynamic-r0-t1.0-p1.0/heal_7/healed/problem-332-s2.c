#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    uintmax_t *frequency,
    size_t frequency_size)
{
    if ((data == NULL && length != 0U) ||
        frequency == NULL ||
        frequency_size < (size_t)UCHAR_MAX + 1U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        const size_t index = (size_t)data[i];

        if (index >= frequency_size || frequency[index] == UINTMAX_MAX) {
            return -1;
        }

        ++frequency[index];
    }

    return 0;
}

int main(void)
{
    enum {
        INPUT_SIZE = 4096,
        FREQUENCY_SIZE = UCHAR_MAX + 1
    };

    unsigned char input[INPUT_SIZE];
    uintmax_t frequency[FREQUENCY_SIZE] = {0};

    for (;;) {
        const size_t bytes_read = fread(input, sizeof input[0], INPUT_SIZE, stdin);

        if (count_character_frequency(
                input,
                bytes_read,
                frequency,
                FREQUENCY_SIZE) != 0) {
            fputs("Frequency counter overflow.\n", stderr);
            return 1;
        }

        if (bytes_read < INPUT_SIZE) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            break;
        }
    }

    for (size_t i = 0U; i < FREQUENCY_SIZE; ++i) {
        if (frequency[i] != 0U &&
            printf("0x%02zX: %ju\n", i, frequency[i]) < 0) {
            fputs("Failed to write output.\n", stderr);
            return 1;
        }
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}