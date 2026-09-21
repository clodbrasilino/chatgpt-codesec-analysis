#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t digits = 0;
    size_t letters = 0;
    unsigned char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof buffer, stdin)) != 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            int character = buffer[i];

            if (isdigit(character)) {
                if (digits == SIZE_MAX) {
                    return EXIT_FAILURE;
                }
                ++digits;
            } else if (isalpha(character)) {
                if (letters == SIZE_MAX) {
                    return EXIT_FAILURE;
                }
                ++letters;
            }
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}