#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int rencontres_number(unsigned int n, unsigned int k, uint64_t *result)
{
    uint64_t derangements[21] = {0};
    uint64_t binomial = 1;
    unsigned int i;

    if (result == NULL || k > n || n > 20U) {
        return 0;
    }

    derangements[0] = 1;

    for (i = 2U; i <= n; ++i) {
        uint64_t sum = derangements[i - 1U] + derangements[i - 2U];

        if (sum > UINT64_MAX / (i - 1U)) {
            return 0;
        }

        derangements[i] = (i - 1U) * sum;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (i = 1U; i <= k; ++i) {
        uint64_t factor = n - k + i;
        uint64_t quotient = binomial / i;
        uint64_t remainder = binomial % i;
        uint64_t first;
        uint64_t second;

        if (quotient > UINT64_MAX / factor) {
            return 0;
        }

        if (remainder != 0U && factor > UINT64_MAX / remainder) {
            return 0;
        }

        first = quotient * factor;
        second = (remainder * factor) / i;

        if (first > UINT64_MAX - second) {
            return 0;
        }

        binomial = first + second;
    }

    if (derangements[n - k] != 0U &&
        binomial > UINT64_MAX / derangements[n - k]) {
        return 0;
    }

    *result = binomial * derangements[n - k];
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    unsigned long n;
    unsigned long k;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n k\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || n > 20UL) {
        fprintf(stderr, "Invalid n\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    k = strtoul(argv[2], &end, 10);

    if (errno != 0 || end == argv[2] || *end != '\0' || k > n) {
        fprintf(stderr, "Invalid k\n");
        return EXIT_FAILURE;
    }

    if (!rencontres_number((unsigned int)n, (unsigned int)k, &result)) {
        fprintf(stderr, "Unable to calculate the rencontres number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}