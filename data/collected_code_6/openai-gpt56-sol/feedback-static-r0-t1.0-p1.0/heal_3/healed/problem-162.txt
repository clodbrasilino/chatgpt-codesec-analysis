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
        uint64_t next = terms + UINT64_C(1);

        if (terms > UINT64_MAX / next) {
            return 0;
        }

        sum = terms * next;
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

int main(int argc, char *argv[])
{
    char *end;
    intmax_t parsed;
    int64_t n;
    int64_t sum;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <integer>\n", program);
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    n = (int64_t)parsed;

    if (!sum_positive_sequence(n, &sum)) {
        fprintf(stderr,
                "Input must be positive and produce a representable sum\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}