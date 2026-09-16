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

    if (ta->second < tb->second) {
        return -1;
    }
    if (ta->second > tb->second) {
        return 1;
    }
    if (ta->first < tb->first) {
        return -1;
    }
    if (ta->first > tb->first) {
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

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        (void)printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }
}

int main(void)
{
    Tuple tuples[] = {
        {3, 9},
        {1, 4},
        {5, 1},
        {2, 4},
        {4, 7}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (sort_tuples(tuples, count) != 0) {
        (void)fprintf(stderr, "Failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    print_tuples(tuples, count);

    return EXIT_SUCCESS;
}