#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binomial(unsigned int n, unsigned int k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL) {
        return -1;
    }

    if (k > n) {
        *result = 0;
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (unsigned int i = 1; i <= k; ++i) {
        unsigned int factor = n - k + i;

        if (value > UINT64_MAX / factor) {
            return -1;
        }

        value *= factor;
        value /= i;
    }

    *result = value;
    return 0;
}

static int sum_of_products(unsigned int n, unsigned int m, uint64_t *result)
{
    uint64_t sum = 0;
    unsigned int limit;

    if (result == NULL) {
        return -1;
    }

    limit = n < m ? n : m;

    for (unsigned int k = 0; k <= limit; ++k) {
        uint64_t first;
        uint64_t second;
        uint64_t product;

        if (binomial(n, k, &first) != 0 ||
            binomial(m, k, &second) != 0) {
            return -1;
        }

        if (first != 0 && second > UINT64_MAX / first) {
            return -1;
        }

        product = first * second;

        if (sum > UINT64_MAX - product) {
            return -1;
        }

        sum += product;
    }

    *result = sum;
    return 0;
}

static int read_unsigned(const char *text, unsigned int *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT_MAX) {
        return -1;
    }

    *value = (unsigned int)parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned int n;
    unsigned int m;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n m\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (read_unsigned(argv[1], &n) != 0 ||
        read_unsigned(argv[2], &m) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_of_products(n, m, &result) != 0) {
        fprintf(stderr, "Arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}