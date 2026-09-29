#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static int count_substrings(const unsigned char *str, size_t length,
                            size_t *result)
{
    if (str == NULL || result == NULL) {
        return -1;
    }

    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t total = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = frequencies[str[i]];

        if (frequency == SIZE_MAX || total > SIZE_MAX - frequency - 1U) {
            return -1;
        }

        total += frequency + 1U;
        frequencies[str[i]] = frequency + 1U;
    }

    *result = total;
    return 0;
}

int main(void)
{
    unsigned char input[INPUT_CAPACITY];
    size_t length = 0;
    int ch = EOF;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= sizeof input) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
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