#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(const unsigned char *str,
                                  size_t length,
                                  unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;

    if (str == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        ++frequencies[str[i]];
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
    unsigned char frequencies_input[1];
    unsigned char result;
    unsigned char current;
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    int ch;
    int has_input = 0;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        current = (unsigned char)ch;
        ++frequencies[current];
        has_input = 1;
    }

    if (ferror(stdin) || !has_input) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            result = (unsigned char)i;
        }
    }

    frequencies_input[0] = result;
    if (!find_max_occurring_character(frequencies_input,
                                      sizeof frequencies_input,
                                      &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%c\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}