#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    int a_last = a->elements[a->length - 1];
    int b_last = b->elements[b->length - 1];

    return (a_last > b_last) - (a_last < b_last);
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL && count != 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (tuples[i].elements == NULL || tuples[i].length == 0) {
            return -1;
        }
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);
    return 0;
}

int main(void)
{
    int values1[] = {3, 5, 2};
    int values2[] = {1, 4, 9};
    int values3[] = {8, 6, 1};
    int values4[] = {7, 3, 5};

    Tuple tuples[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    if (sort_tuples(tuples, tuple_count) != 0) {
        fputs("Failed to sort tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        putchar('(');
        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (printf("%d%s", tuples[i].elements[j],
                       j + 1 < tuples[i].length ? ", " : "") < 0) {
                return EXIT_FAILURE;
            }
        }
        if (puts(")") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}