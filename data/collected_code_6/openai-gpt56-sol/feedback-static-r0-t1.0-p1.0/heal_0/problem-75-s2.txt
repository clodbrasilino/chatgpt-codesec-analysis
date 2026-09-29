#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

static int all_divisible_by(const Tuple *tuple, int k)
{
    if (tuple == NULL || k == 0 || (tuple->length > 0 && tuple->elements == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < tuple->length; ++i) {
        if (tuple->elements[i] % k != 0) {
            return 0;
        }
    }

    return 1;
}

static size_t find_divisible_tuples(const Tuple *tuples, size_t count, int k,
                                    size_t *indices, size_t capacity)
{
    if ((count > 0 && tuples == NULL) || (capacity > 0 && indices == NULL) || k == 0) {
        return 0;
    }

    size_t matches = 0;

    for (size_t i = 0; i < count; ++i) {
        if (all_divisible_by(&tuples[i], k)) {
            if (matches < capacity) {
                indices[matches] = i;
            }
            ++matches;
        }
    }

    return matches;
}

static void print_tuple(const Tuple *tuple)
{
    if (tuple == NULL || (tuple->length > 0 && tuple->elements == NULL)) {
        return;
    }

    putchar('(');

    for (size_t i = 0; i < tuple->length; ++i) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", tuple->elements[i]);
    }

    puts(")");
}

int main(void)
{
    const int values0[] = {6, 12, 18};
    const int values1[] = {3, 7, 9};
    const int values2[] = {24, 30, 42};
    const int values3[] = {5, 10, 15};

    const Tuple tuples[] = {
        {values0, sizeof values0 / sizeof values0[0]},
        {values1, sizeof values1 / sizeof values1[0]},
        {values2, sizeof values2 / sizeof values2[0]},
        {values3, sizeof values3 / sizeof values3[0]}
    };

    const size_t tuple_count = sizeof tuples / sizeof tuples[0];
    const int k = 6;
    size_t *indices = malloc(tuple_count * sizeof *indices);

    if (indices == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    const size_t match_count =
        find_divisible_tuples(tuples, tuple_count, k, indices, tuple_count);

    for (size_t i = 0; i < match_count; ++i) {
        print_tuple(&tuples[indices[i]]);
    }

    free(indices);
    return EXIT_SUCCESS;
}