#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int find_first_repeated_character(const char *str, size_t length,
                                  unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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