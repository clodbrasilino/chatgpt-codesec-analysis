#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(const unsigned char *data, size_t length,
                                  unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == SIZE_MAX) {
            return 0;
        }
        ++frequencies[data[i]];
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            *result = (unsigned char)i;
        }
    }

    return 1;
}

int main(void)
{
    unsigned char buffer[4096];
    size_t length = 0;
    unsigned char result;
    int ch;

    while (length < sizeof buffer && (ch = getchar()) != EOF && ch != '\n') {
        buffer[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (length == sizeof buffer && ch != EOF && ch != '\n') {
        do {
            ch = getchar();
        } while (ch != EOF && ch != '\n');

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(buffer, length, &result)) {
        return EXIT_FAILURE;
    }

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}