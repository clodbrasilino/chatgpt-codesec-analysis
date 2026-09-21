#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && a < INT64_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int minimum_tuple_product(const Tuple *tuples, size_t count,
                                 int64_t *minimum)
{
    int64_t product;

    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    if (!multiply_checked(tuples[0].first, tuples[0].second, minimum)) {
        return 0;
    }

    for (size_t i = 1; i < count; ++i) {
        if (!multiply_checked(tuples[i].first, tuples[i].second, &product)) {
            return 0;
        }

        if (product < *minimum) {
            *minimum = product;
        }
    }

    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    int64_t minimum;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &count) != 1 ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        if (errno != 0) {
            perror("Memory allocation failed");
        } else {
            fputs("Memory allocation failed\n", stderr);
        }
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].first, &tuples[i].second) != 2) {
            fputs("Invalid tuple input\n", stderr);
            goto cleanup;
        }
    }

    if (!minimum_tuple_product(tuples, count, &minimum)) {
        fputs("Unable to calculate product safely\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}