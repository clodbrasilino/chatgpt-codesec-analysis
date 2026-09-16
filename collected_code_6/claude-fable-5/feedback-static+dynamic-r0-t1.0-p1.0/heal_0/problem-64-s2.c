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
    if (tuples == NULL || count == 0) {
        return -1;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void)
{
    size_t count = 5;
    size_t i;
    Tuple *tuples = malloc(count * sizeof(Tuple));

    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    tuples[0].first = 1;
    tuples[0].second = 30;
    tuples[1].first = 2;
    tuples[1].second = 10;
    tuples[2].first = 3;
    tuples[2].second = 20;
    tuples[3].first = 4;
    tuples[3].second = 10;
    tuples[4].first = 5;
    tuples[4].second = 5;

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    free(tuples);
    return EXIT_SUCCESS;
}