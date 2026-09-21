#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (seen[data[i]] != 0U) {
            *result = data[i];
            return 1;
        }

        seen[data[i]] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        unsigned char value = (unsigned char)ch;

        if (seen[value] != 0U) {
            if (putchar(ch) == EOF || putchar('\n') == EOF) {
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }

        seen[value] = 1U;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}