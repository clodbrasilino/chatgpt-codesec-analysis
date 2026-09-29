#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    int value;
    size_t unique_key_count;
} ValueCount;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    if (a->key < b->key) {
        return -1;
    }
    if (a->key > b->key) {
        return 1;
    }
    return 0;
}

static int count_unique_keys_by_value(const Tuple *tuples,
                                      size_t tuple_count,
                                      ValueCount **results,
                                      size_t *result_count)
{
    Tuple *sorted;
    ValueCount *counts;
    size_t count;
    size_t i;
    size_t output_index;

    if (results == NULL || result_count == NULL) {
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuples == NULL ||
        tuple_count > SIZE_MAX / sizeof(*sorted) ||
        tuple_count > SIZE_MAX / sizeof(*counts)) {
        return -1;
    }

    sorted = malloc(tuple_count * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    counts = malloc(tuple_count * sizeof(*counts));
    if (counts == NULL) {
        free(sorted);
        return -1;
    }

    for (i = 0; i < tuple_count; ++i) {
        sorted[i] = tuples[i];
    }

    qsort(sorted, tuple_count, sizeof(*sorted), compare_tuples);

    count = 0;
    output_index = 0;

    for (i = 0; i < tuple_count; ++i) {
        if (i == 0 || sorted[i].value != sorted[i - 1].value) {
            if (i != 0) {
                counts[output_index].unique_key_count = count;
                ++output_index;
            }
            counts[output_index].value = sorted[i].value;
            count = 1;
        } else if (sorted[i].key != sorted[i - 1].key) {
            ++count;
        }
    }

    counts[output_index].unique_key_count = count;
    ++output_index;

    free(sorted);

    *results = counts;
    *result_count = output_index;
    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 10},
        {2, 10},
        {1, 10},
        {3, 20},
        {4, 20},
        {3, 20},
        {5, 30}
    };
    ValueCount *results;
    size_t result_count;
    size_t i;

    if (count_unique_keys_by_value(
            tuples,
            sizeof(tuples) / sizeof(tuples[0]),
            &results,
            &result_count) != 0) {
        fputs("Failed to count unique keys\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        if (printf("%d: %zu\n",
                   results[i].value,
                   results[i].unique_key_count) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);
    return EXIT_SUCCESS;
}