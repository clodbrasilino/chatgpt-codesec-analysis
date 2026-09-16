#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_by_second(const void *left, const void *right)
{
    const Pair *a = left;
    const Pair *b = right;

    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    return 0;
}

static void sort_by_second(Pair *pairs, size_t count)
{
    if (pairs == NULL || count < 2) {
        return;
    }

    qsort(pairs, count, sizeof(*pairs), compare_by_second);
}

int main(void)
{
    Pair pairs[] = {
        {1, 5},
        {2, 3},
        {3, 4},
        {4, 1},
        {5, 2}
    };
    const size_t count = sizeof(pairs) / sizeof(pairs[0]);

    sort_by_second(pairs, count);

    for (size_t i = 0; i < count; ++i) {
        if (printf("%d %d\n", pairs[i].first, pairs[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}