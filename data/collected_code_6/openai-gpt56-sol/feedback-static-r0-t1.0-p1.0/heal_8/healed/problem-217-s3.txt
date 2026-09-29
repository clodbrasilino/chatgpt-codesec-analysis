#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    size_t i;

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char value = data[i];

        if (seen[value] != 0U) {
            *result = value;
            return 1;
        }

        seen[value] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    unsigned char repeated = 0U;
    int found = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        unsigned char value = (unsigned char)ch;

        if (!found && seen[value] != 0U) {
            repeated = value;
            found = 1;
        }

        seen[value] = 1U;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (found) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character found.") == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}