#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;
    int a_last = a->elements[a->length - 1];
    int b_last = b->elements[b->length - 1];

    return (a_last > b_last) - (a_last < b_last);
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL && count != 0) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (tuples[i].elements == NULL || tuples[i].length == 0) {
            return -1;
        }
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);
    return 0;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    for (i = 0; i < count; ++i) {
        putchar('(');
        for (j = 0; j < tuples[i].length; ++j) {
            if (j != 0) {
                printf(", ");
            }
            printf("%d", tuples[i].elements[j]);
        }
        puts(")");
    }
}

int main(void)
{
    int values1[] = {1, 2, 9};
    int values2[] = {3, 4, 2};
    int values3[] = {5, 6, 7};
    int values4[] = {8, 1, 4};

    Tuple tuples[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (sort_tuples(tuples, count) != 0) {
        fputs("Failed to sort tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    print_tuples(tuples, count);
    return EXIT_SUCCESS;
}