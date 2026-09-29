#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    size_t count = 0;
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\n') {
                if (printf("%zu\n", count) < 0) {
                    fputs("Failed to write output.\n", stderr);
                    return EXIT_FAILURE;
                }
                return EXIT_SUCCESS;
            }

            if (count == SIZE_MAX) {
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            ++count;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        if (feof(stdin)) {
            break;
        }
    }

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}