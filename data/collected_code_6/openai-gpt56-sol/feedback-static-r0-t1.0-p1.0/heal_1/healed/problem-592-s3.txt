#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binomial(unsigned int n, unsigned int k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (unsigned int i = 1; i <= k; ++i) {
        uint64_t numerator = (uint64_t)(n - k + i);

        if (value > UINT64_MAX / numerator) {
            return 0;
        }

        value *= numerator;
        value /= i;
    }

    *result = value;
    return 1;
}

static int sum_of_products(unsigned int n, unsigned int m, uint64_t *result)
{
    uint64_t sum = 0;
    unsigned int limit;

    if (result == NULL) {
        return 0;
    }

    limit = n < m ? n : m;

    for (unsigned int k = 0; k <= limit; ++k) {
        uint64_t left;
        uint64_t right;
        uint64_t product;

        if (!binomial(n, k, &left) || !binomial(m, k, &right)) {
            return 0;
        }

        if (left != 0 && right > UINT64_MAX / left) {
            return 0;
        }

        product = left * right;

        if (sum > UINT64_MAX - product) {
            return 0;
        }

        sum += product;
    }

    *result = sum;
    return 1;
}

static int parse_unsigned(const char *text, unsigned int *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' || parsed > UINT_MAX) {
        return 0;
    }

    *value = (unsigned int)parsed;
    return 1;
}

int main(int argc, char * const argv[])
{
    unsigned int n;
    unsigned int m;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n m\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_unsigned(argv[1], &n) || !parse_unsigned(argv[2], &m)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!sum_of_products(n, m, &result)) {
        fprintf(stderr, "Arithmetic overflow or invalid argument\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}