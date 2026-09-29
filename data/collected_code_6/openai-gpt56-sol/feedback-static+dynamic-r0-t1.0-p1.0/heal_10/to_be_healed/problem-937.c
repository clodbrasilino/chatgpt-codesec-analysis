#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *string, size_t length,
                          unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t highest_frequency = 0;
    unsigned char most_common = 0;

    if (string == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = string[i];

        if (frequencies[character] == SIZE_MAX) {
            return 0;
        }

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
    enum { INPUT_CAPACITY = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_CAPACITY];
    size_t length = 0;
    unsigned char result;
    int character;

    while (length < INPUT_CAPACITY &&
           /* Possible weaknesses found:
            * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
            */
           (character = fgetc(stdin)) != EOF &&
           character != '\n') {
        input[length++] = (unsigned char)character;
    }

    if (length == INPUT_CAPACITY) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character != EOF && character != '\n') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = fgetc(stdin)) != EOF && character != '\n') {
            }

            if (ferror(stdin)) {
                perror("Failed to read input");
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        return EXIT_FAILURE;
    }

    if (!most_common_character(input, length, &result)) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputc(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}