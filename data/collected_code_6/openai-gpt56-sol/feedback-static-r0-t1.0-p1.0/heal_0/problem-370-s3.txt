#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    float value;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;

    if (isnan(a->value)) {
        return isnan(b->value) ? 0 : 1;
    }
    if (isnan(b->value)) {
        return -1;
    }
    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
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
        {1, 3.14f},
        {2, -1.25f},
        {3, 2.71f},
        {4, 0.0f}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples_by_float(tuples, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%d, %.2f)\n", tuples[i].id, (double)tuples[i].value) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}