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

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            break;
        }

        unsigned char value = (unsigned char)character;

        if (frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
    }

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    size_t frequencies[CHARACTER_COUNT];

    if (count_character_frequency(stdin, frequencies) != 0) {
        return 1;
    }

    for (size_t i = 0; i < CHARACTER_COUNT; ++i) {
        if (frequencies[i] == 0) {
            continue;
        }

        if (printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            return 1;
        }
    }

    if (fflush(stdout) == EOF) {
        return 1;
    }

    return 0;
}