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
    int last_a = a->elements[a->length - 1];
    int last_b = b->elements[b->length - 1];

    return (last_a > last_b) - (last_a < last_b);
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

static void print_tuples(const Tuple *tuples, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        putchar('(');

        for (size_t j = 0; j < tuples[i].length; ++j) {
            printf("%d", tuples[i].elements[j]);

            if (j + 1 < tuples[i].length) {
                printf(", ");
            }
        }

        printf(")\n");
    }
}

int main(void)
{
    int values1[] = {2, 5};
    int values2[] = {1, 2};
    int values3[] = {4, 4};
    int values4[] = {2, 3};
    int values5[] = {2, 1};

    Tuple tuples[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])},
        {values5, sizeof(values5) / sizeof(values5[0])}
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Failed to sort tuples.\n");
        return EXIT_FAILURE;
    }

    print_tuples(tuples, count);
    return EXIT_SUCCESS;
}