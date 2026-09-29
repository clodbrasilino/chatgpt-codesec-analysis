#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_naturals(uint64_t left, uint64_t right, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || left == 0 || left > right) {
        return 0;
    }

    first = left | UINT64_C(1);
    last = (right & UINT64_C(1)) ? right : right - UINT64_C(1);

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);
    factor = first + count - UINT64_C(1);

    if (factor > UINT64_MAX / count) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed = 0;
    int ch;
    int digit_seen = 0;
    int overflow = 0;

    if (value == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF || ch == '+' || ch == '-') {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        unsigned int digit;

        if (!isdigit((unsigned char)ch)) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        digit_seen = 1;
        digit = (unsigned int)(ch - '0');

        if (parsed > (UINT64_MAX - digit) / UINTMAX_C(10)) {
            overflow = 1;
        } else if (!overflow) {
            parsed = parsed * UINTMAX_C(10) + digit;
        }

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    if (!digit_seen || overflow || ferror(stdin)) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    uint64_t left;
    uint64_t right;
    uint64_t sum;

    if (!read_uint64(&left) ||
        !read_uint64(&right) ||
        !only_whitespace_remains()) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_naturals(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}