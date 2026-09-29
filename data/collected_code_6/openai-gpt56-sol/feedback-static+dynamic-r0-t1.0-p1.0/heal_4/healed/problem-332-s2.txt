#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    uintmax_t frequency[static UCHAR_MAX + 1U])
{
    if (data == NULL || frequency == NULL) {
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
    uintmax_t frequency[UCHAR_MAX + 1U] = {0};

    for (;;) {
        size_t bytes_read = fread(input, 1U, sizeof input, stdin);

        if (bytes_read > 0U &&
            count_character_frequency(input, bytes_read, frequency) != 0) {
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

    for (size_t i = 0; i <= (size_t)UCHAR_MAX; ++i) {
        if (frequency[i] != 0U) {
            if (printf("0x%02zX: %ju\n", i, frequency[i]) < 0) {
                fputs("Failed to write output.\n", stderr);
                return 1;
            }
        }
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}