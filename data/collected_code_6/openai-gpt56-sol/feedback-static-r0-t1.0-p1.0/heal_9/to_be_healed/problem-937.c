#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096U

static int most_common_character(const unsigned char *data, size_t length,
                                 unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t highest_frequency = 0;
    unsigned char most_common = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = data[i];

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
    unsigned char *buffer = malloc(BUFFER_SIZE);
    size_t length = 0;
    unsigned char result;
    int character;

    if (buffer == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= BUFFER_SIZE) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != EOF && character != '\n');

            if (ferror(stdin)) {
                perror("Failed to read input");
            } else {
                fputs("Input is too long.\n", stderr);
            }

            free(buffer);
            return EXIT_FAILURE;
        }

        buffer[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (!most_common_character(buffer, length, &result)) {
        fputs("Input must not be empty.\n", stderr);
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);

    if (fputc((int)result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}