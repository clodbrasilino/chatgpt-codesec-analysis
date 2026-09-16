#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int delannoy_number(unsigned int n, uint64_t *result)
{
    uint64_t term = 1;
    uint64_t sum = 1;

    if (result == NULL) {
        return EINVAL;
    }

    for (unsigned int k = 1; k <= n; ++k) {
        uint64_t numerator = (uint64_t)(n - k + 1U) * 2U;
        uint64_t denominator = k;
        uint64_t gcd = numerator;

        while (denominator != 0U) {
            uint64_t remainder = gcd % denominator;
            gcd = denominator;
            denominator = remainder;
        }

        numerator /= gcd;
        denominator = (uint64_t)k / gcd;

        if (term % denominator != 0U ||
            term / denominator > UINT64_MAX / numerator) {
            return ERANGE;
        }

        term = (term / denominator) * numerator;

        if (sum > UINT64_MAX - term) {
            return ERANGE;
        }

        sum += term;
    }

    *result = sum;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    status = delannoy_number((unsigned int)input, &result);
    if (status != 0) {
        fputs("Result is outside the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}