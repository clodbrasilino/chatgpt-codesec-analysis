#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int most_common_character(const unsigned char *string, size_t length,
                          unsigned char *result, size_t *count)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t highest = 0;
    unsigned char most_common = 0;

    if (string == NULL || result == NULL || count == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = string[i];

        if (frequencies[character] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[character];

        if (frequencies[character] > highest) {
            highest = frequencies[character];
            most_common = character;
        }
    }

    *result = most_common;
    *count = highest;
    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_CAPACITY];
    unsigned char character;
    size_t count;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == sizeof input) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return 1;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (most_common_character(input, length, &character, &count) != 0) {
        fputs("Input must not be empty.\n", stderr);
        return 1;
    }

    if (printf("%c %zu\n", (int)character, count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}