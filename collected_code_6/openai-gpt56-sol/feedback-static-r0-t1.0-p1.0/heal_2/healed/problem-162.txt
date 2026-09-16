#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_positive_sequence(int64_t n, int64_t *result)
{
    uint64_t terms;
    uint64_t sum;

    if (result == NULL || n <= 0) {
        return 0;
    }

    terms = ((uint64_t)n + UINT64_C(1)) / UINT64_C(2);

    if ((n & INT64_C(1)) == 0) {
        if (terms > UINT64_MAX / (terms + UINT64_C(1))) {
            return 0;
        }
        sum = terms * (terms + UINT64_C(1));
    } else {
        if (terms > UINT64_MAX / terms) {
            return 0;
        }
        sum = terms * terms;
    }

    if (sum > (uint64_t)INT64_MAX) {
        return 0;
    }

    *result = (int64_t)sum;
    return 1;
}

int main(int argc, char *const argv[const])
{
    char *end = NULL;
    intmax_t parsed;
    int64_t n;
    int64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoimax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    n = (int64_t)parsed;

    if (!sum_positive_sequence(n, &sum)) {
        fprintf(stderr,
                "Input must be positive and produce a representable sum\n");
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", sum);
    return EXIT_SUCCESS;
}