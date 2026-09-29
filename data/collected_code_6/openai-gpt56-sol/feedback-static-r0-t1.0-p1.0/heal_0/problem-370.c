#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int key;
    float value;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;
    const int a_nan = isnan(a->value);
    const int b_nan = isnan(b->value);

    if (a_nan || b_nan) {
        if (a_nan && b_nan) {
            return 0;
        }
        return a_nan ? 1 : -1;
    }

    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    return 0;
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL && count != 0U) {
        return -1;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 3.5f},
        {2, -1.2f},
        {3, 7.0f},
        {4, 0.0f},
        {5, 2.8f}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (sort_tuples(tuples, count) != 0) {
        fputs("Failed to sort tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%d, %.2f)\n", tuples[i].key, (double)tuples[i].value) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}