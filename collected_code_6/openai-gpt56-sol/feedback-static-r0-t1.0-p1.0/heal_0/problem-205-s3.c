#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    long long first;
    long long second;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;

    if (a->first < b->first) {
        return -1;
    }
    if (a->first > b->first) {
        return 1;
    }
    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    return 0;
}

static int count_and_merge(long long *values, long long *buffer,
                           size_t left, size_t right, uint64_t *count)
{
    if (right - left <= 1U) {
        return 0;
    }

    size_t middle = left + (right - left) / 2U;

    if (count_and_merge(values, buffer, left, middle, count) != 0 ||
        count_and_merge(values, buffer, middle, right, count) != 0) {
        return -1;
    }

    size_t i = left;
    size_t j = middle;
    size_t k = left;

    while (i < middle && j < right) {
        if (values[i] <= values[j]) {
            buffer[k++] = values[i++];
        } else {
            uint64_t added = (uint64_t)(middle - i);

            if (UINT64_MAX - *count < added) {
                return -1;
            }

            *count += added;
            buffer[k++] = values[j++];
        }
    }

    while (i < middle) {
        buffer[k++] = values[i++];
    }

    while (j < right) {
        buffer[k++] = values[j++];
    }

    for (k = left; k < right; ++k) {
        values[k] = buffer[k];
    }

    return 0;
}

static int find_tuple_inversions(Tuple *tuples, size_t count,
                                 uint64_t *inversions)
{
    if (inversions == NULL || (count > 0U && tuples == NULL)) {
        return -1;
    }

    *inversions = 0U;

    if (count < 2U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*tuples) ||
        count > SIZE_MAX / sizeof(long long)) {
        return -1;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);

    long long *values = malloc(count * sizeof(*values));
    long long *buffer = malloc(count * sizeof(*buffer));

    if (values == NULL || buffer == NULL) {
        free(values);
        free(buffer);
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        values[i] = tuples[i].second;
    }

    int result = count_and_merge(values, buffer, 0U, count, inversions);

    free(buffer);
    free(values);

    return result;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(Tuple)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    Tuple *tuples = NULL;

    if (count > 0U) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lld %lld", &tuples[i].first, &tuples[i].second) != 2) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    uint64_t inversions;

    if (find_tuple_inversions(tuples, count, &inversions) != 0) {
        fputs("Unable to calculate inversions\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%llu\n", (unsigned long long)inversions);

    free(tuples);
    return EXIT_SUCCESS;
}