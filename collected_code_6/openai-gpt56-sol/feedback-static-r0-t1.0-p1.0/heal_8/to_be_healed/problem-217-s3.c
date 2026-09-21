#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    uintmax_t seen = 0;
    size_t i;

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        const unsigned char value = data[i];
        /* Possible weaknesses found:
         *  use of undeclared identifier 'UINTMAX_WIDTH'
         *  'UINTMAX_WIDTH' undeclared (first use in this function); did you mean 'UINT_WIDTH'?
         *  each undeclared identifier is reported only once for each function it appears in
         */
        const uintmax_t mask = UINTMAX_C(1) << (value % UINTMAX_WIDTH);

        if ((seen & mask) != 0U) {
            *result = value;
            return 1;
        }

        seen |= mask;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char data[UCHAR_MAX + 1U];
    size_t length = 0U;
    unsigned char repeated;
    int ch;
    int status;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (length < sizeof data && (ch = getchar()) != EOF && ch != '\n') {
        data[length++] = (unsigned char)ch;
    }

    if (ch != '\n' && ch != EOF) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != EOF && ch != '\n') {
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    status = find_first_repeated_character(data, length, &repeated);

    if (status < 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0) {
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