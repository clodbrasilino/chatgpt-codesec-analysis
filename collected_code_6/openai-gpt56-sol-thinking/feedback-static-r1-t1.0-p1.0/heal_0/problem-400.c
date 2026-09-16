#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple tuple;
    size_t frequency;
} TupleFrequency;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

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

static int extract_tuple_frequencies(const Tuple *tuples,
                                     size_t tuple_count,
                                     TupleFrequency **frequencies,
                                     size_t *unique_count)
{
    Tuple *sorted;
    TupleFrequency *result;
    size_t count;
    size_t result_index;
    size_t i;

    if (frequencies == NULL || unique_count == NULL) {
        return 0;
    }

    *frequencies = NULL;
    *unique_count = 0;

    if (tuple_count == 0) {
        return 1;
    }

    if (tuples == NULL ||
        tuple_count > SIZE_MAX / sizeof(*sorted) ||
        tuple_count > SIZE_MAX / sizeof(*result)) {
        return 0;
    }

    sorted = malloc(tuple_count * sizeof(*sorted));
    if (sorted == NULL) {
        return 0;
    }

    for (i = 0; i < tuple_count; ++i) {
        sorted[i] = tuples[i];
    }

    qsort(sorted, tuple_count, sizeof(*sorted), compare_tuples);

    count = 1;
    for (i = 1; i < tuple_count; ++i) {
        if (compare_tuples(&sorted[i - 1], &sorted[i]) != 0) {
            ++count;
        }
    }

    result = calloc(count, sizeof(*result));
    if (result == NULL) {
        free(sorted);
        return 0;
    }

    result_index = 0;
    result[0].tuple = sorted[0];
    result[0].frequency = 1;

    for (i = 1; i < tuple_count; ++i) {
        if (compare_tuples(&sorted[i - 1], &sorted[i]) == 0) {
            ++result[result_index].frequency;
        } else {
            ++result_index;
            result[result_index].tuple = sorted[i];
            result[result_index].frequency = 1;
        }
    }

    free(sorted);
    *frequencies = result;
    *unique_count = count;

    return 1;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4},
        {1, 2},
        {7, 8}
    };
    TupleFrequency *frequencies = NULL;
    size_t unique_count = 0;
    size_t i;

    if (!extract_tuple_frequencies(
            tuples,
            sizeof(tuples) / sizeof(tuples[0]),
            &frequencies,
            &unique_count)) {
        fputs("Failed to extract tuple frequencies\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; ++i) {
        printf("(%d, %d): %zu\n",
               frequencies[i].tuple.first,
               frequencies[i].tuple.second,
               frequencies[i].frequency);
    }

    free(frequencies);
    return EXIT_SUCCESS;
}