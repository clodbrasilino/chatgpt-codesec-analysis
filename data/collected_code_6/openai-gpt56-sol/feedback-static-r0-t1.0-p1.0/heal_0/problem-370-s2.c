#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int integer;
    float real;
} Tuple;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    const int a_nan = isnan(a->real);
    const int b_nan = isnan(b->real);

    if (a_nan || b_nan) {
        if (a_nan && b_nan) {
            return 0;
        }
        return a_nan ? 1 : -1;
    }

    if (a->real < b->real) {
        return -1;
    }
    if (a->real > b->real) {
        return 1;
    }
    return 0;
}

static void sort_tuples_by_float(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count < 2U) {
        return;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);
}

int main(void)
{
    Tuple tuples[] = {
        {1, 3.5f},
        {2, -1.2f},
        {3, 7.8f},
        {4, 0.0f},
        {5, 2.4f}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples_by_float(tuples, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%d, %.2f)\n", tuples[i].integer, (double)tuples[i].real) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}