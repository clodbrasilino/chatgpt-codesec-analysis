#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    size_t count = 0;
    unsigned char *buffer = malloc(4096);

    if (buffer == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, 1, 4096, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\n') {
                int result = printf("%zu\n", count);
                free(buffer);

                if (result < 0) {
                    fputs("Failed to write output.\n", stderr);
                    return EXIT_FAILURE;
                }

                return EXIT_SUCCESS;
            }

            if (count == SIZE_MAX) {
                fputs("Input is too long.\n", stderr);
                free(buffer);
                return EXIT_FAILURE;
            }

            ++count;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(buffer);
            return EXIT_FAILURE;
        }

        if (feof(stdin)) {
            break;
        }
    }

    int result = printf("%zu\n", count);
    free(buffer);

    if (result < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}