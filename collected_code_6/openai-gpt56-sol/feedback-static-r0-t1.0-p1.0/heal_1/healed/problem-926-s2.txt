#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int rencontres(unsigned int n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 0;

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 1;
    }

    for (unsigned int i = 2U; i <= n; ++i) {
        uint64_t factor = (uint64_t)(i - 1U);
        uint64_t sum;

        if (UINT64_MAX - current < previous) {
            return 0;
        }

        sum = current + previous;

        if (sum > UINT64_MAX / factor) {
            return 0;
        }

        previous = current;
        current = factor * sum;
    }

    *result = current;
    return 1;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        input > (unsigned long)UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!rencontres((unsigned int)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}