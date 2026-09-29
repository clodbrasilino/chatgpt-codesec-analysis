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
    unsigned char *buffer = malloc(4096);
    size_t count = 0;

    if (buffer == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, 1, 4096, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (is_vowel(buffer[i])) {
                if (count == SIZE_MAX) {
                    fputs("Vowel count overflow.\n", stderr);
                    free(buffer);
                    return EXIT_FAILURE;
                }
                ++count;
            }
        }

        if (bytes_read < 4096) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(buffer);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    free(buffer);

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}