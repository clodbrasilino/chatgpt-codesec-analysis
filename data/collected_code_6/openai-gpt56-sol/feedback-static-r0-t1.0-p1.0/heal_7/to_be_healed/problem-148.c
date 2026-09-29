#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t digit_sum(uint64_t value)
{
    uint64_t sum = 0;

    do {
        sum += value % UINT64_C(10);
        value /= UINT64_C(10);
    } while (value != 0);

    return sum;
}

static void divide_max_digit_sum(uint64_t number,
                                 uint64_t *first,
                                 uint64_t *second)
{
    uint64_t power = UINT64_C(1);

    while (power <= number / UINT64_C(10)) {
        power *= UINT64_C(10);
    }

    *first = power - UINT64_C(1);
    *second = number - *first;
}

int main(void)
{
    uintmax_t parsed;
    uint64_t number;
    uint64_t first;
    uint64_t second;
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF || ch == '-' || ch == '+') {
        return EXIT_FAILURE;
    }

    if (!isdigit((unsigned char)ch)) {
        return EXIT_FAILURE;
    }

    parsed = 0;

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (parsed > (UINT64_MAX - digit) / UINTMAX_C(10)) {
            return EXIT_FAILURE;
        }

        parsed = parsed * UINTMAX_C(10) + digit;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isdigit((unsigned char)ch));

    if (parsed == 0) {
        return EXIT_FAILURE;
    }

    while (ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed;
    divide_max_digit_sum(number, &first, &second);

    if (printf("%" PRIu64 " %" PRIu64 "\n", first, second) < 0 ||
        printf("%" PRIu64 "\n",
               digit_sum(first) + digit_sum(second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}