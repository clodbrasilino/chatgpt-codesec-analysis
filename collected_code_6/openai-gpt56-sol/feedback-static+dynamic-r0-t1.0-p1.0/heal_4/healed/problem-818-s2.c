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
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (islower((unsigned char)ch) != 0) {
            if (count == SIZE_MAX) {
                fputs("Lowercase count overflow.\n", stderr);
                return EXIT_FAILURE;
            }
            ++count;
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