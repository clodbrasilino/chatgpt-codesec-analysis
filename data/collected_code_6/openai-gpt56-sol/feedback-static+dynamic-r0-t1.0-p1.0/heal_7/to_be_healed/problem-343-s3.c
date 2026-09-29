#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    uintmax_t digits = 0;
    uintmax_t letters = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            int ch = buffer[i];

            if (isdigit(ch)) {
                if (digits == UINTMAX_MAX) {
                    return EXIT_FAILURE;
                }
                ++digits;
            } else if (isalpha(ch)) {
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

    if (printf("Digits: %" PRIuMAX "\nLetters: %" PRIuMAX "\n",
               digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}