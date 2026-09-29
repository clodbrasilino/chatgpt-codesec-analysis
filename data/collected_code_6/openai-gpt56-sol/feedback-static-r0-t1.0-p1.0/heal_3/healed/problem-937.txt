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
    unsigned char buffer[4096];
    size_t length = 0;
    int character;
    unsigned char result;

    while (length < sizeof buffer) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        buffer[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        return EXIT_FAILURE;
    }

    if (length == sizeof buffer) {
        character = fgetc(stdin);

        if (character != EOF && character != '\n') {
            fputs("Input is too long.\n", stderr);
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

    if (fputc(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        perror("Failed to flush output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}