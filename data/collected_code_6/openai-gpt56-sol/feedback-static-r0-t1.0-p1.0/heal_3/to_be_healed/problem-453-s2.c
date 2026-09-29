#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        uint64_t quotient;

        if (number % divisor != 0) {
            continue;
        }

        quotient = number / divisor;

        if ((divisor & UINT64_C(1)) == 0) {
            if (divisor > UINT64_MAX - total) {
                return 0;
            }
            total += divisor;
        }

        if (quotient != divisor && (quotient & UINT64_C(1)) == 0) {
            if (quotient > UINT64_MAX - total) {
                return 0;
            }
            total += quotient;
        }
    }

    *sum = total;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *start;
    char *end;
    uintmax_t parsed;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (*start != '\0' &&
           (*start == ' ' || *start == '\t' || *start == '\n' ||
            *start == '\r' || *start == '\f' || *start == '\v')) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0 ||
        parsed > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' &&
           (*end == ' ' || *end == '\t' || *end == '\n' ||
            *end == '\r' || *end == '\f' || *end == '\v')) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_factors((uint64_t)parsed, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}