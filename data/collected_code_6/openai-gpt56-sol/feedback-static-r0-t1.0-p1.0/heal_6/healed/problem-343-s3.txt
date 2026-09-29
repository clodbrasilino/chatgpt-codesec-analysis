#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t digits = 0;
    size_t letters = 0;
    unsigned char *buffer = malloc(4096);

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, 1, 4096, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            int character = buffer[i];

            if (isdigit(character)) {
                if (digits == SIZE_MAX) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                ++digits;
            } else if (isalpha(character)) {
                if (letters == SIZE_MAX) {
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

    free(buffer);

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}