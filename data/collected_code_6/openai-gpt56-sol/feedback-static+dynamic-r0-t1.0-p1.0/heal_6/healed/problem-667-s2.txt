#include <ctype.h>
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
    unsigned char buffer[4096];
    size_t count = 0;

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (is_vowel(buffer[i])) {
                if (count == SIZE_MAX) {
                    fputs("Vowel count overflow.\n", stderr);
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

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}