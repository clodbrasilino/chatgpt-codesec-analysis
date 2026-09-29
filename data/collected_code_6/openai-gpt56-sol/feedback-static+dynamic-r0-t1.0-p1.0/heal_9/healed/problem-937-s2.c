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
    unsigned char input[INPUT_CAPACITY];
    unsigned char character;
    size_t count;
    size_t length = 0;
    int ch;

    while (length < sizeof input &&
           (ch = fgetc(stdin)) != EOF &&
           ch != '\n') {
        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (length == sizeof input) {
        ch = fgetc(stdin);

        if (ch != EOF && ch != '\n') {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return 1;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }
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