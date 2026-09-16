#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_COUNT 5
#define NAME_LEN 32

typedef struct {
    char name[NAME_LEN];
    float value;
} Tuple;

static int compare_tuples(const void *a, const void *b)
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

static void sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0U; i < count; i++) {
        if (printf("(%s, %.2f)\n", tuples[i].name, (double)tuples[i].value) < 0) {
            break;
        }
    }
}

int main(void)
{
    Tuple tuples[TUPLE_COUNT] = {
        { "alpha", 3.14f },
        { "beta", 1.41f },
        { "gamma", 2.72f },
        { "delta", 0.58f },
        { "epsilon", 1.62f }
    };

    if (printf("Before sorting:\n") < 0) {
        return EXIT_FAILURE;
    }
    print_tuples(tuples, TUPLE_COUNT);

    sort_tuples(tuples, TUPLE_COUNT);

    if (printf("After sorting:\n") < 0) {
        return EXIT_FAILURE;
    }
    print_tuples(tuples, TUPLE_COUNT);

    return EXIT_SUCCESS;
}