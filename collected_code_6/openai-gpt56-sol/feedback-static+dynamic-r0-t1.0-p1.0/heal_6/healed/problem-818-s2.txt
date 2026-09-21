#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_lowercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (islower((unsigned char)*string) != 0) {
            if (count == SIZE_MAX) {
                return SIZE_MAX;
            }
            ++count;
        }
        ++string;
    }

    return count;
}

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
            if (islower(buffer[i]) != 0) {
                if (count == SIZE_MAX) {
                    fputs("Lowercase count overflow.\n", stderr);
                    free(buffer);
                    return EXIT_FAILURE;
                }
                ++count;
            }
        }

        if (bytes_read < 4096) {
            if (ferror(stdin) != 0) {
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