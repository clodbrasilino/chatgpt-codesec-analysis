#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int find_first_repeated_character(const unsigned char *data, size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        const unsigned char value = data[i];

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
    unsigned char buffer[4096];

    for (;;) {
        const size_t bytes_read = fread(buffer, 1U, sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            const unsigned char value = buffer[i];

            if (seen[value] != 0U) {
                if (fputc((int)value, stdout) == EOF ||
                    fputc('\n', stdout) == EOF) {
                    return 1;
                }

                return 0;
            }

            seen[value] = 1U;
        }

        if (bytes_read != sizeof buffer) {
            if (ferror(stdin) != 0) {
                if (fputs("Failed to read input.\n", stderr) == EOF) {
                    return 1;
                }

                return 1;
            }

            break;
        }
    }

    if (fputs("No repeated character found.\n", stdout) == EOF) {
        return 1;
    }

    return 0;
}