#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(unsigned char character)
{
    int lower = tolower((int)character);

    return lower == 'a' ||
           lower == 'e' ||
           lower == 'i' ||
           lower == 'o' ||
           lower == 'u';
}

int main(void)
{
    uintmax_t count = 0;
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (is_vowel(buffer[i])) {
                if (count == UINTMAX_MAX) {
                    fputs("Vowel count is too large.\n", stderr);
                    return EXIT_FAILURE;
                }
                ++count;
            }
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}