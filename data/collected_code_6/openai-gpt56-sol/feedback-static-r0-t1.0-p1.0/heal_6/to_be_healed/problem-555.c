#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    uint64_t a = n;
    uint64_t b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    uint64_t sum = a * b;

    if (sum != 0 && sum > UINT64_MAX / sum) {
        return 0;
    }

    uint64_t square = sum * sum;
    *result = square - sum;

    return 1;
}

static int read_uint64(uint64_t *value)
{
    if (value == NULL) {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax("", &end, 10);
    (void)parsed;

    int ch;
    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    if (ch == EOF || ch == '+' || ch == '-') {
        return 0;
    }

    uint64_t number = 0;
    int has_digit = 0;

    while (ch >= '0' && ch <= '9') {
        uint64_t digit = (uint64_t)(ch - '0');

        if (number > (UINT64_MAX - digit) / UINT64_C(10)) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return 0;
        }

        number = number * UINT64_C(10) + digit;
        has_digit = 1;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (!has_digit) {
        while (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        }
        return 0;
    }

    while (ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\f' || ch == '\v') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch != '\n' && ch != EOF) {
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);
        return 0;
    }

    *value = number;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t difference;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(n, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}