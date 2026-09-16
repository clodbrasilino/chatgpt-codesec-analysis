#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int sum_alternate_chains(const Tuple *tuples, size_t count,
                                int64_t *first_chain_sum,
                                int64_t *second_chain_sum)
{
    int64_t first_sum = 0;
    int64_t second_sum = 0;

    if (first_chain_sum == NULL || second_chain_sum == NULL) {
        return 0;
    }

    if (count > 0 && tuples == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t first_value = (i % 2 == 0) ? tuples[i].first : tuples[i].second;
        int64_t second_value = (i % 2 == 0) ? tuples[i].second : tuples[i].first;

        if (!add_checked(first_sum, first_value, &first_sum) ||
            !add_checked(second_sum, second_value, &second_sum)) {
            return 0;
        }
    }

    *first_chain_sum = first_sum;
    *second_chain_sum = second_sum;
    return 1;
}

int main(void)
{
    size_t count = 0;
    Tuple *tuples = NULL;
    int64_t first_chain_sum = 0;
    int64_t second_chain_sum = 0;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        errno = 0;
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            if (errno != 0) {
                perror("malloc");
            } else {
                fputs("Memory allocation failed\n", stderr);
            }
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].first, &tuples[i].second) != 2) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!sum_alternate_chains(tuples, count,
                              &first_chain_sum, &second_chain_sum)) {
        fputs("Unable to calculate sums\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 " %" PRId64 "\n",
           first_chain_sum, second_chain_sum);

    free(tuples);
    return EXIT_SUCCESS;
}