#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sum_odd_factors(uint64_t number, uint64_t *result)
{
    uint64_t sum = UINT64_C(1);

    if (number == 0 || result == NULL) {
        return 0;
    }

    while ((number & UINT64_C(1)) == 0) {
        number /= UINT64_C(2);
    }

    for (uint64_t factor = UINT64_C(3);
         factor <= number / factor;
         factor += UINT64_C(2)) {
        uint64_t term = UINT64_C(1);
        uint64_t power = UINT64_C(1);

        while (number % factor == 0) {
            number /= factor;

            if (power > UINT64_MAX / factor) {
                return 0;
            }
            power *= factor;

            if (term > UINT64_MAX - power) {
                return 0;
            }
            term += power;
        }

        if (sum > UINT64_MAX / term) {
            return 0;
        }
        sum *= term;
    }

    if (number > UINT64_C(1)) {
        uint64_t term;

        if (number == UINT64_MAX) {
            return 0;
        }
        term = number + UINT64_C(1);

        if (sum > UINT64_MAX / term) {
            return 0;
        }
        sum *= term;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed == 0 ||
        parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_factors((uint64_t)parsed, &result)) {
        fputs("The sum cannot be represented as uint64_t.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}