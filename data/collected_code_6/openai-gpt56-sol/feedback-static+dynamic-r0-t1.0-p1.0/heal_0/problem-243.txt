#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    size_t original_index;
    size_t frequency;
} Tuple;

static int compare_frequency_desc(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->frequency < b->frequency) {
        return 1;
    }
    if (a->frequency > b->frequency) {
        return -1;
    }
    if (a->original_index > b->original_index) {
        return 1;
    }
    if (a->original_index < b->original_index) {
        return -1;
    }
    return 0;
}

static int sort_by_first_occurrence(Tuple *tuples, size_t count)
{
    if (tuples == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        size_t frequency = 0U;

        tuples[i].original_index = i;

        for (size_t j = 0U; j < count; ++j) {
            if (tuples[i].first == tuples[j].first) {
                ++frequency;
            }
        }

        tuples[i].frequency = frequency;
    }

    qsort(tuples, count, sizeof(*tuples), compare_frequency_desc);
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {3, 10, 0U, 0U},
        {1, 20, 0U, 0U},
        {3, 30, 0U, 0U},
        {2, 40, 0U, 0U},
        {1, 50, 0U, 0U},
        {3, 60, 0U, 0U}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (sort_by_first_occurrence(tuples, count) != 0) {
        fputs("Failed to sort tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%d, %d)%c",
                   tuples[i].first,
                   tuples[i].second,
                   i + 1U == count ? '\n' : ' ') < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}