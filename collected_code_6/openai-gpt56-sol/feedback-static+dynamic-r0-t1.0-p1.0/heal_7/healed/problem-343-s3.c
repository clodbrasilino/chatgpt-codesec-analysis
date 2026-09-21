#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    uintmax_t digits = 0;
    uintmax_t letters = 0;
    unsigned char *buffer = malloc(4096);

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, 1, 4096, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            int ch = buffer[i];

            if (isdigit(ch)) {
                if (digits == UINTMAX_MAX) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                ++digits;
            } else if (isalpha(ch)) {
                if (letters == UINTMAX_MAX) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                ++letters;
            }
        }

        if (bytes_read < 4096) {
            if (ferror(stdin)) {
                free(buffer);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    if (printf("Digits: %" PRIuMAX "\nLetters: %" PRIuMAX "\n",
               digits, letters) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}