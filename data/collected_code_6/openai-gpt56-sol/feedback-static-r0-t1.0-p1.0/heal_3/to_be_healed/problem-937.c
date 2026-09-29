#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *data, size_t length,
                          unsigned char *result)
{
    size_t frequencies[256] = {0};
    size_t highest_frequency = 0;
    unsigned char most_common = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = data[i];

        ++frequencies[character];
        if (frequencies[character] > highest_frequency) {
            highest_frequency = frequencies[character];
            most_common = character;
        }
    }

    *result = most_common;
    return 1;
}

int main(void)
{
    size_t frequencies[256] = {0};
    size_t highest_frequency = 0;
    unsigned char most_common = 0;
    int character;
    int has_input = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        unsigned char value = (unsigned char)character;

        has_input = 1;
        ++frequencies[value];

        if (frequencies[value] > highest_frequency) {
            highest_frequency = frequencies[value];
            most_common = value;
        }
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        return EXIT_FAILURE;
    }

    if (!has_input) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputc(most_common, stdout) == EOF || fputc('\n', stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        perror("Failed to flush output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}