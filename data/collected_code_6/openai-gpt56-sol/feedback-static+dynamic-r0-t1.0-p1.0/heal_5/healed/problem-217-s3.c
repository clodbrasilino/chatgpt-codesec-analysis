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
    unsigned char buffer[4096];

    while (!feof(stdin)) {
        size_t bytes_read = fread(buffer, 1U, sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            unsigned char value = buffer[i];

            if (seen[value] != 0U) {
                if (fputc((int)value, stdout) == EOF ||
                    fputc('\n', stdout) == EOF) {
                    return 1;
                }

                return 0;
            }

            seen[value] = 1U;
        }

        if (ferror(stdin)) {
            if (fputs("Failed to read input.\n", stderr) == EOF) {
                return 1;
            }
            return 1;
        }
    }

    if (fputs("No repeated character found.\n", stdout) == EOF) {
        return 1;
    }

    return 0;
}