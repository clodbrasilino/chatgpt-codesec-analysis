#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 32
#define TUPLE_COUNT 5

typedef struct {
    char name[NAME_LEN];
    int id;
    float value;
} Tuple;

static int compare_by_float(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;

    if (ta->value < tb->value) {
        return -1;
    }
    if (ta->value > tb->value) {
        return 1;
    }
    return 0;
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return -1;
    }
    qsort(tuples, count, sizeof(Tuple), compare_by_float);
    return 0;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        (void)printf("(%s, %d, %.2f)\n",
                     tuples[i].name, tuples[i].id, (double)tuples[i].value);
    }
}

int main(void)
{
    Tuple tuples[TUPLE_COUNT] = {
        { "alpha",   1, 3.14f },
        { "beta",    2, 1.41f },
        { "gamma",   3, 2.72f },
        { "delta",   4, 0.58f },
        { "epsilon", 5, 1.62f }
    };

    (void)printf("Before sorting:\n");
    print_tuples(tuples, TUPLE_COUNT);

    if (sort_tuples(tuples, TUPLE_COUNT) != 0) {
        (void)fprintf(stderr, "Error: failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    (void)printf("After sorting:\n");
    print_tuples(tuples, TUPLE_COUNT);

    return EXIT_SUCCESS;
}