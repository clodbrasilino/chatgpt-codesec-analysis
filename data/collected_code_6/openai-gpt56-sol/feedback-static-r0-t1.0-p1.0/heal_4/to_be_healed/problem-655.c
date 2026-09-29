#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sum_fifth_powers(uint64_t n, uint64_t *result)
{
    __uint128_t value;
    __uint128_t square;

    if (result == NULL) {
        return -1;
    }

    value = (__uint128_t)n * ((__uint128_t)n + 1);
    square = 2 * (__uint128_t)n * n + 2 * (__uint128_t)n - 1;
    value = value * square / 12;

    if (value > UINT64_MAX) {
        return -1;
    }

    *result = (uint64_t)value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (const char *p = input; p < end; ++p) {
        if (!isspace((unsigned char)*p)) {
            if (*p == '-') {
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_fifth_powers((uint64_t)parsed, &sum) != 0) {
        fputs("Result out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}