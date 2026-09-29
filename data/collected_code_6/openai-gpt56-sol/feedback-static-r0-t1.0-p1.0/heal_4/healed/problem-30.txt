#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const unsigned char *str, size_t length,
                            size_t *result)
{
    size_t frequencies[256] = {0};
    size_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = frequencies[str[i]];

        if (frequency == SIZE_MAX ||
            total > SIZE_MAX - frequency - 1) {
            return -1;
        }

        frequencies[str[i]] = frequency + 1;
        total += frequency + 1;
    }

    *result = total;
    return 0;
}

int main(void)
{
    enum { INPUT_SIZE = 4096 };
    unsigned char input[INPUT_SIZE];
    size_t length = 0;
    int ch = EOF;

    while (length < sizeof input) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == sizeof input) {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }
    }

    if (ch == EOF && length == 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count = 0;

    if (count_substrings(input, length, &count) != 0) {
        fputs("Unable to count substrings.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}