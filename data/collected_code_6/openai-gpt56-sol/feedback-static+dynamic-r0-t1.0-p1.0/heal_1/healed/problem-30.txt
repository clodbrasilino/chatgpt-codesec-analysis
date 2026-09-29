#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const unsigned char *str, size_t length, size_t *result)
{
    if (str == NULL || result == NULL) {
        return -1;
    }

    size_t frequencies[256] = {0};
    size_t total = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = frequencies[str[i]];

        if (frequency == SIZE_MAX || total > SIZE_MAX - frequency - 1) {
            return -1;
        }

        total += frequency + 1;
        frequencies[str[i]] = frequency + 1;
    }

    *result = total;
    return 0;
}

int main(void)
{
    unsigned char input[4096];
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == sizeof(input)) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count;

    if (count_substrings(input, length, &count) != 0) {
        fputs("Unable to count substrings.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}