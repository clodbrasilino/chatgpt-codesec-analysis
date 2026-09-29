#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    uintmax_t digits = 0;
    uintmax_t letters = 0;
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (isdigit((int)buffer[i])) {
                if (digits == UINTMAX_MAX) {
                    return EXIT_FAILURE;
                }
                ++digits;
            } else if (isalpha((int)buffer[i])) {
                if (letters == UINTMAX_MAX) {
                    return EXIT_FAILURE;
                }
                ++letters;
            }
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }
    }

    if (printf("Digits: %ju\nLetters: %ju\n", digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}