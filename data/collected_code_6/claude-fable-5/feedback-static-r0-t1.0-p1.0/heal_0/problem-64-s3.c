#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;

    if (ta->first < tb->first) {
        return -1;
    }
    if (ta->first > tb->first) {
        return 1;
    }
    if (ta->second < tb->second) {
        return -1;
    }
    if (ta->second > tb->second) {
        return 1;
    }
    return 0;
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return -1;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {3, 4},
        {1, 9},
        {2, 5},
        {1, 2},
        {3, 1}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    if (sort_tuples(tuples, count) != 0) {
        (void)fprintf(stderr, "Failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}