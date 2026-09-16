#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float value;
    char label[32];
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;

    if (tuple_a->value < tuple_b->value) {
        return -1;
    }
    if (tuple_a->value > tuple_b->value) {
        return 1;
    }
    return 0;
}

int sort_tuples(Tuple *tuples, size_t count)
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
        {1, 3.14f, "Pi"},
        {2, 1.41f, "Sqrt2"},
        {3, 2.71f, "Euler"},
        {4, 0.57f, "Gamma"},
        {5, 1.61f, "Golden"}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        printf("ID: %d, Value: %.2f, Label: %s\n",
               tuples[i].id, tuples[i].value, tuples[i].label);
    }

    return EXIT_SUCCESS;
}