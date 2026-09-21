#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int find_first_repeated_character(const char *str, size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)str[i];

        if (seen[ch] != 0U) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    for (;;) {
        int ch = getchar();

        if (ch == EOF) {
            break;
        }

        unsigned char value = (unsigned char)ch;

        if (seen[value] != 0U) {
            if (putchar((int)value) == EOF || putchar('\n') == EOF) {
                return 1;
            }

            return 0;
        }

        seen[value] = 1U;
    }

    if (ferror(stdin)) {
        (void)fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (fputs("No repeated character found.\n", stdout) == EOF) {
        return 1;
    }

    return 0;
}