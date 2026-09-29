#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 1;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 2; i <= n; ++i) {
        if (UINT64_MAX - current < previous) {
            return -1;
        }

        uint64_t next = current + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

static int read_input(size_t *value)
{
    uintmax_t input = 0;
    int ch;
    int digit_seen = 0;
    int trailing_space = 0;
    int overflow = 0;

    if (value == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && ch != '\n' && isspace((unsigned char)ch));

    if (ch == EOF || ch == '\n' || ch == '+' || ch == '-') {
        return -1;
    }

    while (ch != EOF && ch != '\n') {
        if (isdigit((unsigned char)ch)) {
            unsigned int digit = (unsigned int)(ch - '0');

            if (trailing_space) {
                overflow = 1;
            } else if (input > (UINTMAX_MAX - digit) / 10) {
                overflow = 1;
            } else {
                input = input * 10 + digit;
            }

            digit_seen = 1;
        } else if (isspace((unsigned char)ch)) {
            trailing_space = 1;
        } else {
            overflow = 1;
        }

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    if (!digit_seen || overflow || input > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

int main(void)
{
    size_t input;
    uint64_t result;

    if (read_input(&input) != 0) {
        return EXIT_FAILURE;
    }

    if (count_tilings(input, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}