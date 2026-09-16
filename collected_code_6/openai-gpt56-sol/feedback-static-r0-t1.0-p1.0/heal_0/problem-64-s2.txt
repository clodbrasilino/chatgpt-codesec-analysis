#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef int (*TupleComparator)(const Tuple *, const Tuple *);

static int compare_tuples(const Tuple *left, const Tuple *right)
{
    if (left->first < right->first) {
        return -1;
    }
    if (left->first > right->first) {
        return 1;
    }
    if (left->second < right->second) {
        return -1;
    }
    if (left->second > right->second) {
        return 1;
    }
    return 0;
}

static void sort_tuples(Tuple *tuples, size_t count, TupleComparator comparator)
{
    if (tuples == NULL || comparator == NULL || count < 2U) {
        return;
    }

    for (size_t i = 1U; i < count; ++i) {
        Tuple current = tuples[i];
        size_t j = i;

        while (j > 0U && comparator(&current, &tuples[j - 1U]) < 0) {
            tuples[j] = tuples[j - 1U];
            --j;
        }

        tuples[j] = current;
    }
}

int main(void)
{
    Tuple tuples[] = {
        {3, 2},
        {1, 5},
        {2, 4},
        {1, 2},
        {3, 1}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, count, compare_tuples);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}