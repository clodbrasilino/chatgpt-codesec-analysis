#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    size_t frequency;
} Tuple;

static bool tuples_equal(const Tuple *left, const Tuple *right)
{
    return left->first == right->first && left->second == right->second;
}

static bool assign_tuple_frequencies(Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL && count != 0U) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        tuples[i].frequency = 0U;

        for (j = 0U; j < count; ++j) {
            if (tuples_equal(&tuples[i], &tuples[j])) {
                ++tuples[i].frequency;
            }
        }
    }

    return true;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2, 0U},
        {3, 4, 0U},
        {1, 2, 0U},
        {5, 6, 0U},
        {3, 4, 0U},
        {1, 2, 0U}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    if (!assign_tuple_frequencies(tuples, count)) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("(%d, %d): %zu\n",
                   tuples[i].first,
                   tuples[i].second,
                   tuples[i].frequency) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}