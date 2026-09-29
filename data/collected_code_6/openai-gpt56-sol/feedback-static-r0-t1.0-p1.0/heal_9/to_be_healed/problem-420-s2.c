#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <ctype.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return -1;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return -1;
    }

    a *= b;

    if (a != 0 && a > UINT64_MAX / a) {
        return -1;
    }

    a *= a;

    if (a > UINT64_MAX / UINT64_C(2)) {
        return -1;
    }

    *result = a * UINT64_C(2);
    return 0;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    uintmax_t limit;
    int ch;
    int digit_seen = 0;
    int trailing_space = 0;

    if (value == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch) && ch != '\n');

    if (ch == '\n' || ch == '+' || ch == '-') {
        return -1;
    }

    parsed = 0;
    limit = (uintmax_t)UINT64_MAX;

    while (ch != '\n' && ch != EOF) {
        if (isdigit((unsigned char)ch)) {
            unsigned int digit = (unsigned int)(ch - '0');

            if (trailing_space) {
                return -1;
            }

            digit_seen = 1;

            if (parsed > (limit - digit) / UINTMAX_C(10)) {
                return -1;
            }

            parsed = parsed * UINTMAX_C(10) + digit;
        } else if (isspace((unsigned char)ch)) {
            trailing_space = 1;
        } else {
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    if (!digit_seen) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (read_uint64(&n) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_sum_even(n, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}