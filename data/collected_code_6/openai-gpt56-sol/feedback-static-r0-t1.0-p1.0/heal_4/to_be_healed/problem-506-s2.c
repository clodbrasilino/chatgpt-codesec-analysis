#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int permutation_coefficient(unsigned long long n,
                                   unsigned long long k,
                                   unsigned long long *result)
{
    unsigned long long value = 1;

    if (result == NULL || k > n) {
        return 0;
    }

    for (unsigned long long i = 0; i < k; ++i) {
        unsigned long long factor = n - i;

        if (factor != 0 && value > ULLONG_MAX / factor) {
            return 0;
        }

        value *= factor;
    }

    *result = value;
    return 1;
}

static int read_unsigned_long_long(const char *text,
                                   unsigned long long *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '\0' || text[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned long long n;
    unsigned long long k;
    unsigned long long result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n k\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!read_unsigned_long_long(argv[1], &n) ||
        !read_unsigned_long_long(argv[2], &k)) {
        fprintf(stderr, "n and k must be nonnegative integers.\n");
        return EXIT_FAILURE;
    }

    if (k > n) {
        fprintf(stderr, "k must not exceed n.\n");
        return EXIT_FAILURE;
    }

    if (!permutation_coefficient(n, k, &result)) {
        fprintf(stderr,
                "The permutation coefficient exceeds the supported range.\n");
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}