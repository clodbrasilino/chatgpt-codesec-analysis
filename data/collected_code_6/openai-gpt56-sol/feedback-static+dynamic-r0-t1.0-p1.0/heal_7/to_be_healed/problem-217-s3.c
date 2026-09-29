#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int find_first_repeated_character(const unsigned char *data, size_t length,
                                  unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (data == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

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

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                (void)fputs("Failed to read input.\n", stderr);
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