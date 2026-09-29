#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_of_power(unsigned int base, unsigned int exponent,
                              unsigned long long *result)
{
    unsigned long long value = 1;
    unsigned long long sum = 0;

    if (result == NULL) {
        return -1;
    }

    for (unsigned int i = 0; i < exponent; ++i) {
        if (base != 0U && value > ULLONG_MAX / base) {
            return -1;
        }
        value *= base;
    }

    do {
        sum += value % 10ULL;
        value /= 10ULL;
    } while (value != 0ULL);

    *result = sum;
    return 0;
}

int main(int argc, char const *const argv[])
{
    char *end = NULL;
    unsigned long parsed_base;
    unsigned long parsed_exponent;
    unsigned long long result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <exponent>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_base = strtoul(argv[1], &end, 10);
    if (errno != 0 || end == argv[1] || *end != '\0' ||
        parsed_base > UINT_MAX) {
        fprintf(stderr, "Invalid base\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_exponent = strtoul(argv[2], &end, 10);
    if (errno != 0 || end == argv[2] || *end != '\0' ||
        parsed_exponent > UINT_MAX) {
        fprintf(stderr, "Invalid exponent\n");
        return EXIT_FAILURE;
    }

    if (digit_sum_of_power((unsigned int)parsed_base,
                           (unsigned int)parsed_exponent,
                           &result) != 0) {
        fprintf(stderr, "The power exceeds the supported numeric range\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}