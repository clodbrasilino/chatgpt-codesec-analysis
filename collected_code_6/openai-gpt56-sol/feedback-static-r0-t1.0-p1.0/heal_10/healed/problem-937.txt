#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096U

static int most_common_character(const unsigned char *data, size_t length,
                                 unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t highest_frequency = 0U;
    unsigned char most_common = 0U;

    if (data == NULL || result == NULL || length == 0U) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
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
    unsigned char buffer[BUFFER_SIZE];
    size_t length = 0U;
    unsigned char result = 0U;
    int character;

    while (length < sizeof buffer &&
           (character = getchar()) != EOF &&
           character != '\n') {
        buffer[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        return EXIT_FAILURE;
    }

    if (length == sizeof buffer) {
        character = getchar();

        if (character != EOF && character != '\n') {
            do {
                character = getchar();
            } while (character != EOF && character != '\n');

            if (ferror(stdin)) {
                perror("Failed to read input");
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            perror("Failed to read input");
            return EXIT_FAILURE;
        }
    }

    if (!most_common_character(buffer, length, &result)) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputc((int)result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}