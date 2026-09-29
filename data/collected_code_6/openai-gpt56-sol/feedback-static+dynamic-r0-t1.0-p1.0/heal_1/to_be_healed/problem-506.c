#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int permutation_coefficient(uint64_t n, uint64_t k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || k > n) {
        return 0;
    }

    for (uint64_t i = 0; i < k; ++i) {
        uint64_t factor = n - i;

        if (factor != 0 && value > UINT64_MAX / factor) {
            return 0;
        }

        value *= factor;
    }

    *result = value;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    uint64_t n;
    uint64_t k;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n k\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &n) || !parse_uint64(argv[2], &k)) {
        fprintf(stderr, "Error: n and k must be nonnegative integers.\n");
        return EXIT_FAILURE;
    }

    if (k > n) {
        fprintf(stderr, "Error: k must not exceed n.\n");
        return EXIT_FAILURE;
    }

    if (!permutation_coefficient(n, k, &result)) {
        fprintf(stderr, "Error: permutation coefficient exceeds uint64_t range.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}