#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (result == NULL || (data == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = data[i];

        if (seen[ch]) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1;
    }

    return 0;
}

int main(void)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};
    unsigned char repeated = 0;
    int found = 0;
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        unsigned char ch = (unsigned char)c;

        if (!found) {
            if (seen[ch]) {
                repeated = ch;
                found = 1;
            } else {
                seen[ch] = 1;
            }
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (found) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}