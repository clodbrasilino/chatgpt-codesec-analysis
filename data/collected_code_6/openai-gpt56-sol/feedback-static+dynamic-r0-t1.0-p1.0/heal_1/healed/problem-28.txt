#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binomial_coefficient(uint32_t n, uint32_t k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (uint32_t i = 1; i <= k; ++i) {
        uint64_t numerator = (uint64_t)(n - k) + i;
        uint64_t denominator = i;
        uint64_t a = numerator;
        uint64_t b = denominator;

        while (b != 0) {
            uint64_t remainder = a % b;
            a = b;
            b = remainder;
        }

        numerator /= a;
        denominator /= a;

        a = value;
        b = denominator;

        while (b != 0) {
            uint64_t remainder = a % b;
            a = b;
            b = remainder;
        }

        value /= a;
        denominator /= a;

        if (denominator != 1 || value > UINT64_MAX / numerator) {
            return 0;
        }

        value *= numerator;
    }

    *result = value;
    return 1;
}

int main(void)
{
    char input[128];
    char extra;
    char *end;
    uintmax_t parsed_n;
    uintmax_t parsed_k;
    uint32_t n;
    uint32_t k;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    parsed_n = strtoumax(end, &end, 10);

    if (errno == ERANGE || end == input || parsed_n > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *k_start = end;
    errno = 0;
    parsed_k = strtoumax(k_start, &end, 10);

    if (errno == ERANGE || end == k_start || parsed_k > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(end, " %c", &extra) == 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint32_t)parsed_n;
    k = (uint32_t)parsed_k;

    if (!binomial_coefficient(n, k, &result)) {
        fputs("Invalid arguments or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}