#include <limits.h>
#include <stdint.h>
#include <stdio.h>

enum { CHARACTER_COUNT = UCHAR_MAX + 1 };

static int count_character_frequency(
    FILE *stream,
    size_t *frequencies,
    size_t frequency_count)
{
    if (stream == NULL ||
        frequencies == NULL ||
        frequency_count < CHARACTER_COUNT) {
        return -1;
    }

    for (size_t i = 0; i < CHARACTER_COUNT; ++i) {
        frequencies[i] = 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    while (!feof(stream)) {
        const size_t bytes_read = fread(buffer, sizeof buffer[0],
                                        sizeof buffer / sizeof buffer[0],
                                        stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            const size_t value = buffer[i];

            if (value >= frequency_count || frequencies[value] == SIZE_MAX) {
                return -1;
            }

            ++frequencies[value];
        }

        if (ferror(stream)) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    size_t frequencies[CHARACTER_COUNT];

    if (count_character_frequency(
            stdin,
            frequencies,
            sizeof frequencies / sizeof frequencies[0]) != 0) {
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