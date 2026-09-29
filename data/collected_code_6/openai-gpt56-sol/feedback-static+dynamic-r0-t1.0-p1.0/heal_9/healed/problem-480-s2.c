#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(const unsigned long frequencies[UCHAR_MAX + 1],
                                  unsigned char *result)
{
    unsigned long max_count = 0;

    if (frequencies == NULL || result == NULL) {
        return 0;
    }

    for (unsigned int i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            *result = (unsigned char)i;
        }
    }

    return max_count != 0;
}

int main(void)
{
    unsigned long frequencies[UCHAR_MAX + 1] = {0};
    unsigned char result;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        unsigned char value = (unsigned char)ch;

        if (frequencies[value] == ULONG_MAX) {
            return EXIT_FAILURE;
        }

        ++frequencies[value];
    }

    if (ferror(stdin) ||
        !find_max_occurring_character(frequencies, &result)) {
        return EXIT_FAILURE;
    }

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}