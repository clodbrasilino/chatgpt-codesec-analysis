#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int first_non_repeated_character(const unsigned char *data, size_t length,
                                 unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned int index = data[i];

        if (frequencies[index] == SIZE_MAX) {
            return 0;
        }

        ++frequencies[index];
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[4096];
    size_t length = 0;
    unsigned char result;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == sizeof input) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        fputs("No input provided.\n", stderr);
        return EXIT_FAILURE;
    }

    if (first_non_repeated_character(input, length, &result)) {
        if (fputc(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    } else if (fputs("No non-repeated character found.\n", stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}