#include <ctype.h>
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
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    unsigned char buffer[4096];
    size_t count = 0;
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof buffer, stdin)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            if (islower(buffer[i]) != 0) {
                ++count;
            }
        }
    }

    if (ferror(stdin) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}