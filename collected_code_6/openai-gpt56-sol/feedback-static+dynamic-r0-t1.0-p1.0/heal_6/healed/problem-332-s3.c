#include <limits.h>
#include <stdint.h>
#include <stdio.h>

enum { CHARACTER_COUNT = UCHAR_MAX + 1 };

static int count_character_frequency(
    FILE *stream,
    size_t frequencies[static CHARACTER_COUNT])
{
    if (stream == NULL || frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0; i < CHARACTER_COUNT; ++i) {
        frequencies[i] = 0;
    }

    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            unsigned int value = buffer[i];

            if (frequencies[value] == SIZE_MAX) {
                return -1;
            }

            ++frequencies[value];
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stream)) {
                return -1;
            }

            if (feof(stream)) {
                break;
            }
        }
    }

    return 0;
}

int main(void)
{
    size_t frequencies[CHARACTER_COUNT];

    if (count_character_frequency(stdin, frequencies) != 0) {
        return 1;
    }

    for (size_t i = 0; i < CHARACTER_COUNT; ++i) {
        if (frequencies[i] != 0 &&
            printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            return 1;
        }
    }

    return fflush(stdout) == EOF ? 1 : 0;
}