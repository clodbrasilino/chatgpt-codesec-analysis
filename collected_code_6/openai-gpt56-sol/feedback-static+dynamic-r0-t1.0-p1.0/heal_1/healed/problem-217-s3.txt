#include <limits.h>
#include <stdio.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (str == NULL || result == NULL) {
        return -1;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str;

        if (seen[ch] != 0U) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1U;
        ++str;
    }

    return 0;
}

int main(void)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};
    int ch;

    while ((ch = getchar()) != EOF) {
        unsigned char value = (unsigned char)ch;

        if (seen[value] != 0U) {
            if (putchar(ch) == EOF || putchar('\n') == EOF) {
                return 1;
            }
            return 0;
        }

        seen[value] = 1U;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (fputs("No repeated character found.\n", stdout) == EOF) {
        return 1;
    }

    return 0;
}