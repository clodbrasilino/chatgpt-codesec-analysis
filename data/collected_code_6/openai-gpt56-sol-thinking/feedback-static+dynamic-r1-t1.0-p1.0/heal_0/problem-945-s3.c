#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int tuples_equal(const Tuple *left, const Tuple *right)
{
    return left->first == right->first && left->second == right->second;
}

static int tuples_to_set(const Tuple *tuples, size_t tuple_count,
                         Tuple **set, size_t *set_count)
{
    Tuple *result;
    size_t unique_count = 0U;

    if (set == NULL || set_count == NULL) {
        return -1;
    }

    *set = NULL;
    *set_count = 0U;

    if (tuple_count == 0U) {
        return 0;
    }

    if (tuples == NULL || tuple_count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(tuple_count * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < tuple_count; ++i) {
        int duplicate = 0;

        for (size_t j = 0U; j < unique_count; ++j) {
            if (tuples_equal(&tuples[i], &result[j])) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            result[unique_count] = tuples[i];
            ++unique_count;
        }
    }

    *set = result;
    *set_count = unique_count;
    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    Tuple *set = NULL;
    size_t set_count = 0U;

    if (tuples_to_set(tuples, tuple_count, &set, &set_count) != 0) {
        fputs("Failed to convert tuples to a set.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < set_count; ++i) {
        if (printf("(%d, %d)\n", set[i].first, set[i].second) < 0) {
            free(set);
            return EXIT_FAILURE;
        }
    }

    free(set);
    return EXIT_SUCCESS;
}