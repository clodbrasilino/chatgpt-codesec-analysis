#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int compute_sum(unsigned int n, unsigned int m,
                       unsigned long long *result)
{
    const unsigned int limit = n < m ? n : m;
    unsigned long long c_n = 1;
    unsigned long long c_m = 1;
    unsigned long long sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (unsigned int k = 0; k <= limit; ++k) {
        unsigned long long product;

        if (c_m != 0 && c_n > ULLONG_MAX / c_m) {
            return 0;
        }

        product = c_n * c_m;

        if (sum > ULLONG_MAX - product) {
            return 0;
        }

        sum += product;

        if (k < limit) {
            const unsigned long long n_factor =
                (unsigned long long)n - k;
            const unsigned long long m_factor =
                (unsigned long long)m - k;
            const unsigned long long divisor =
                (unsigned long long)k + 1;

            if (c_n > ULLONG_MAX / n_factor ||
                c_m > ULLONG_MAX / m_factor) {
                return 0;
            }

            c_n = (c_n * n_factor) / divisor;
            c_m = (c_m * m_factor) / divisor;
        }
    }

    *result = sum;
    return 1;
}

static int parse_unsigned(const char *text, unsigned int *value)
{
    char *end = NULL;
    unsigned long parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoul(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT_MAX) {
        return 0;
    }

    *value = (unsigned int)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned int n;
    unsigned int m;
    unsigned long long result;
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", program_name);
        return EXIT_FAILURE;
    }

    if (!parse_unsigned(argv[1], &n) ||
        !parse_unsigned(argv[2], &m)) {
        fprintf(stderr, "Invalid nonnegative integer input\n");
        return EXIT_FAILURE;
    }

    if (!compute_sum(n, m, &result)) {
        fprintf(stderr, "Arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}