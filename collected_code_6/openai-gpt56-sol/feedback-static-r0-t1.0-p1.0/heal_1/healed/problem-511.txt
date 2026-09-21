#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_factor_sum(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t factor = 2;

    if (n == 0 || result == NULL) {
        return 0;
    }

    while (factor <= n / factor) {
        while (n % factor == 0) {
            if (sum > UINT64_MAX - factor) {
                return 0;
            }

            sum += factor;
            n /= factor;
        }

        factor = factor == 2 ? 3 : factor + 2;
    }

    if (n > 1) {
        if (sum > UINT64_MAX - n) {
            return 0;
        }

        sum += n;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    uintmax_t parsed;
    uint64_t result;
    char *end;

    if (getline(&input, &capacity, stdin) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno != 0 || end == input || parsed == 0 || parsed > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (!minimum_factor_sum((uint64_t)parsed, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}