#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int key;
    long long value;
} Tuple;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->key < b->key) {
        return -1;
    }
    if (a->key > b->key) {
        return 1;
    }
    return 0;
}

static int maximum_aggregate(Tuple *tuples, size_t count, long long *result)
{
    if (tuples == NULL || result == NULL || count == 0U) {
        return -1;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);

    long long maximum = 0;
    long long aggregate = tuples[0].value;
    int current_key = tuples[0].key;

    for (size_t i = 1U; i < count; ++i) {
        if (tuples[i].key == current_key) {
            if (__builtin_add_overflow(aggregate, tuples[i].value, &aggregate)) {
                return -1;
            }
        } else {
            if (aggregate > maximum || i == 1U) {
                maximum = aggregate;
            }
            current_key = tuples[i].key;
            aggregate = tuples[i].value;
        }
    }

    if (aggregate > maximum || count == 1U) {
        maximum = aggregate;
    }

    *result = maximum;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {1, 15},
        {3, 5},
        {2, 30}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long result = 0;

    if (maximum_aggregate(tuples, count, &result) != 0) {
        fputs("Unable to calculate the maximum aggregate.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}