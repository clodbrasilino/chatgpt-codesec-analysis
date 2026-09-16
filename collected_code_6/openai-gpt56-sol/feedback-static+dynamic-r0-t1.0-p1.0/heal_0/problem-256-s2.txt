#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_primes(uint64_t limit, uint64_t *count)
{
    unsigned char *is_composite;
    uint64_t result = 0;
    uint64_t i;

    if (count == NULL) {
        return -1;
    }

    *count = 0;

    if (limit <= 2) {
        return 0;
    }

    if (limit > (uint64_t)SIZE_MAX) {
        return -1;
    }

    is_composite = calloc((size_t)limit, sizeof(*is_composite));
    if (is_composite == NULL) {
        return -1;
    }

    for (i = 2; i <= (limit - 1) / i; ++i) {
        uint64_t multiple;

        if (is_composite[i] != 0U) {
            continue;
        }

        for (multiple = i * i; multiple < limit; multiple += i) {
            is_composite[multiple] = 1U;
        }
    }

    for (i = 2; i < limit; ++i) {
        if (is_composite[i] == 0U) {
            ++result;
        }
    }

    free(is_composite);
    *count = result;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Input must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid non-negative integer.\n");
        return EXIT_FAILURE;
    }

    if (count_primes((uint64_t)parsed, &count) != 0) {
        fprintf(stderr, "Unable to count primes.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count);
    return EXIT_SUCCESS;
}