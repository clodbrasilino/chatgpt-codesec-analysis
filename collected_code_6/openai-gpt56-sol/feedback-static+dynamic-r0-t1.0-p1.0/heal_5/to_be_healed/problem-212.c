#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = UINT64_C(71581);
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;

    if (result == NULL || n > max_n) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);
    d = n * n + n - UINT64_C(1);

    if (a % UINT64_C(2) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    if (a % UINT64_C(5) == 0) {
        a /= UINT64_C(5);
    } else if (b % UINT64_C(5) == 0) {
        b /= UINT64_C(5);
    } else if (c % UINT64_C(5) == 0) {
        c /= UINT64_C(5);
    } else {
        d /= UINT64_C(5);
    }

    *result = a * b * c * d;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    char *number_start;
    uintmax_t value;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '\0' || *end == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    number_start = end;
    errno = 0;
    value = strtoumax(number_start, &end, 10);

    if (errno == ERANGE || end == number_start || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fourth_powers((uint64_t)value, &sum)) {
        fputs("Result exceeds uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}