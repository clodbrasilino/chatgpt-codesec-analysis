#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (result == NULL || (data == NULL && length > 0U)) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    unsigned char result = 0U;
    int repeated = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        const unsigned char value = (unsigned char)ch;

        if (repeated == 0 && seen[value] != 0U) {
            result = value;
            repeated = 1;
        }

        seen[value] = 1U;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (repeated != 0) {
        if (putchar((int)result) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}