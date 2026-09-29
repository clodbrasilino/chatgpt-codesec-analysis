#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    return strcmp(a->first, b->first);
}

static void sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples != NULL && count > 1U) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }
}

int main(void)
{
    Tuple tuples[] = {
        {"pear", "green"},
        {"apple", "red"},
        {"orange", "orange"},
        {"banana", "yellow"}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%s, %s)\n", tuples[i].first, tuples[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}