#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    uintmax_t digits = 0;
    uintmax_t letters = 0;
    unsigned char buffer[4096];

    while (!feof(stdin)) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < bytes_read; ++i) {
            unsigned char ch = buffer[i];

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
    }

    if (printf("Digits: %" PRIuMAX "\nLetters: %" PRIuMAX "\n",
               digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}