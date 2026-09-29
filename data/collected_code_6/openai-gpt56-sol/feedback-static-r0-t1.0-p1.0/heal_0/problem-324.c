#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_alternate_chains(const int (*tuples)[2], size_t count,
                                long long sums[2])
{
    size_t i;

    if (sums == NULL || (count > 0U && tuples == NULL)) {
        return -1;
    }

    sums[0] = 0;
    sums[1] = 0;

    for (i = 0; i < count; ++i) {
        if ((tuples[i][0] > 0 && sums[0] > LLONG_MAX - tuples[i][0]) ||
            (tuples[i][0] < 0 && sums[0] < LLONG_MIN - tuples[i][0]) ||
            (tuples[i][1] > 0 && sums[1] > LLONG_MAX - tuples[i][1]) ||
            (tuples[i][1] < 0 && sums[1] < LLONG_MIN - tuples[i][1])) {
            return -1;
        }

        sums[0] += tuples[i][0];
        sums[1] += tuples[i][1];
    }

    return 0;
}

static int read_size(size_t *value)
{
    unsigned long long input;

    if (value == NULL || scanf("%llu", &input) != 1) {
        return -1;
    }

    if (input > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

int main(void)
{
    int (*tuples)[2] = NULL;
    long long sums[2];
    size_t count;
    size_t i;

    if (read_size(&count) != 0) {
        fputs("Invalid tuple count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < count; ++i) {
        if (scanf("%d %d", &tuples[i][0], &tuples[i][1]) != 2) {
            fputs("Invalid tuple input.\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (sum_alternate_chains(tuples, count, sums) != 0) {
        fputs("Unable to calculate sums.\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%lld %lld\n", sums[0], sums[1]) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}