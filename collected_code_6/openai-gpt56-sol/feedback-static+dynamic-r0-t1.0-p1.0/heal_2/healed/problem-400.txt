#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (a->first != b->first) {
        return (a->first > b->first) - (a->first < b->first);
    }

    return (a->second > b->second) - (a->second < b->second);
}

static int get_tuple_frequencies(const Tuple *tuples, size_t count,
                                 TupleFrequency **frequencies,
                                 size_t *unique_count)
{
    Tuple *sorted = NULL;
    TupleFrequency *result = NULL;
    size_t result_count = 0;
    size_t tuple_bytes;
    size_t result_bytes;
    size_t i;

    if (frequencies == NULL || unique_count == NULL) {
        return -1;
    }

    *frequencies = NULL;
    *unique_count = 0;

    if (count == 0) {
        return 0;
    }

    if (tuples == NULL ||
        count > SIZE_MAX / sizeof(*sorted) ||
        count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    tuple_bytes = count * sizeof(*sorted);
    result_bytes = count * sizeof(*result);

    sorted = malloc(tuple_bytes);
    if (sorted == NULL) {
        return -1;
    }

    result = malloc(result_bytes);
    if (result == NULL) {
        free(sorted);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        sorted[i] = tuples[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_tuples);

    for (i = 0; i < count; ++i) {
        if (result_count == 0 ||
            compare_tuples(&sorted[i],
                           &result[result_count - 1].tuple) != 0) {
            result[result_count].tuple = sorted[i];
            result[result_count].frequency = 1;
            ++result_count;
        } else {
            ++result[result_count - 1].frequency;
        }
    }

    free(sorted);

    if (result_count < count) {
        TupleFrequency *resized =
            realloc(result, result_count * sizeof(*result));

        if (resized != NULL) {
            result = resized;
        }
    }

    *frequencies = result;
    *unique_count = result_count;

    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4},
        {1, 2}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    TupleFrequency *frequencies = NULL;
    size_t unique_count = 0;
    size_t i;

    if (get_tuple_frequencies(tuples, count, &frequencies,
                              &unique_count) != 0) {
        fputs("Failed to extract tuple frequencies.\n", stderr);
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