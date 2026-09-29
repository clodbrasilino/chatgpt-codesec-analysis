#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *string,
                          size_t length,
                          unsigned char *character,
                          size_t *count)
{
    size_t frequencies[256] = {0};
    size_t max_count = 0;
    unsigned char most_common = 0;

    if (string == NULL || character == NULL || count == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char value = string[i];

        if (frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
    }

    for (size_t i = 0; i < 256; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            most_common = (unsigned char)i;
        }
    }

    *character = most_common;
    *count = max_count;
    return 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    unsigned char *input = malloc((size_t)MAX_INPUT_LENGTH);
    size_t length = 0;
    unsigned char character = 0;
    size_t count = 0;
    int ch;

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length >= (size_t)MAX_INPUT_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        fputs("Input must not be empty.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (most_common_character(input, length, &character, &count) != 0) {
        fputs("Failed to process input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (character >= 32U && character <= 126U) {
        printf("Most common character: '%c'\nCount: %zu\n",
               (int)character, count);
    } else {
        printf("Most common character: 0x%02X\nCount: %zu\n",
               (unsigned int)character, count);
    }

    free(input);
    return EXIT_SUCCESS;
}