#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    int64_t sum;
} Pair;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int64_t pair_sum(int first, int second)
{
    return (int64_t)first + (int64_t)second;
}

static int find_k_pairs(const int *first,
                        size_t first_size,
                        const int *second,
                        size_t second_size,
                        size_t k,
                        Pair **pairs,
                        size_t *pair_count)
{
    int *sorted_first = NULL;
    int *sorted_second = NULL;
    size_t *indices = NULL;
    Pair *result = NULL;
    size_t limit;
    size_t count = 0;

    if (pairs == NULL || pair_count == NULL) {
        return EINVAL;
    }

    *pairs = NULL;
    *pair_count = 0;

    if (k == 0 || first_size == 0 || second_size == 0) {
        return 0;
    }

    if (first == NULL || second == NULL) {
        return EINVAL;
    }

    if (first_size > SIZE_MAX / second_size) {
        limit = k;
    } else {
        size_t total = first_size * second_size;
        limit = k < total ? k : total;
    }

    if (first_size > SIZE_MAX / sizeof(*sorted_first) ||
        second_size > SIZE_MAX / sizeof(*sorted_second) ||
        first_size > SIZE_MAX / sizeof(*indices) ||
        limit > SIZE_MAX / sizeof(*result)) {
        return EOVERFLOW;
    }

    sorted_first = malloc(first_size * sizeof(*sorted_first));
    sorted_second = malloc(second_size * sizeof(*sorted_second));
    indices = calloc(first_size, sizeof(*indices));
    result = malloc(limit * sizeof(*result));

    if (sorted_first == NULL || sorted_second == NULL ||
        indices == NULL || result == NULL) {
        free(sorted_first);
        free(sorted_second);
        free(indices);
        free(result);
        return ENOMEM;
    }

    for (size_t i = 0; i < first_size; ++i) {
        sorted_first[i] = first[i];
    }

    for (size_t i = 0; i < second_size; ++i) {
        sorted_second[i] = second[i];
    }

    qsort(sorted_first, first_size, sizeof(*sorted_first), compare_ints);
    qsort(sorted_second, second_size, sizeof(*sorted_second), compare_ints);

    while (count < limit) {
        size_t best_row = SIZE_MAX;
        int64_t best_sum = INT64_MAX;

        for (size_t i = 0; i < first_size; ++i) {
            if (indices[i] < second_size) {
                int64_t sum = pair_sum(sorted_first[i],
                                       sorted_second[indices[i]]);

                if (best_row == SIZE_MAX || sum < best_sum) {
                    best_row = i;
                    best_sum = sum;
                }
            }
        }

        if (best_row == SIZE_MAX) {
            break;
        }

        result[count].first = sorted_first[best_row];
        result[count].second = sorted_second[indices[best_row]];
        result[count].sum = best_sum;
        ++indices[best_row];
        ++count;
    }

    free(sorted_first);
    free(sorted_second);
    free(indices);

    *pairs = result;
    *pair_count = count;
    return 0;
}

int main(void)
{
    const int first[] = {1, 7, 11};
    const int second[] = {2, 4, 6};
    const size_t k = 4;
    Pair *pairs = NULL;
    size_t pair_count = 0;
    int status = find_k_pairs(first,
                              sizeof(first) / sizeof(first[0]),
                              second,
                              sizeof(second) / sizeof(second[0]),
                              k,
                              &pairs,
                              &pair_count);

    if (status != 0) {
        fprintf(stderr, "Unable to find pairs: error %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < pair_count; ++i) {
        if (printf("(%d, %d), sum = %" PRId64 "\n",
                   pairs[i].first,
                   pairs[i].second,
                   pairs[i].sum) < 0) {
            free(pairs);
            return EXIT_FAILURE;
        }
    }

    free(pairs);
    return EXIT_SUCCESS;
}