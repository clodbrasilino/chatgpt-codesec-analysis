#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
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

static int is_inversion(const Tuple *a, const Tuple *b)
{
    return (a->first < b->first && a->second > b->second) ||
           (a->first > b->first && a->second < b->second);
}

static int find_inversions(Tuple *tuples, size_t count, size_t *result)
{
    size_t inversions = 0;

    if (result == NULL || (tuples == NULL && count != 0)) {
        return -1;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (is_inversion(&tuples[i], &tuples[j])) {
                if (inversions == SIZE_MAX) {
                    return -1;
                }
                ++inversions;
                printf("(%d, %d) and (%d, %d)\n",
                       tuples[i].first, tuples[i].second,
                       tuples[j].first, tuples[j].second);
            }
        }
    }

    *result = inversions;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 4},
        {2, 3},
        {3, 1},
        {4, 2},
        {5, 5}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t inversion_count = 0;

    errno = 0;

    if (find_inversions(tuples, count, &inversion_count) != 0) {
        fputs("Failed to find inversions.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Total inversions: %zu\n", inversion_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}