#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static bool trim_each_tuple_by_k(TupleList *list, size_t k)
{
    if (list == NULL || (list->count > 0 && list->tuples == NULL)) {
        return false;
    }

    for (size_t i = 0; i < list->count; ++i) {
        const Tuple *tuple = &list->tuples[i];

        if (tuple->length > 0 && tuple->values == NULL) {
            return false;
        }

        if (k > tuple->length || k > tuple->length - k) {
            return false;
        }

        size_t new_length = tuple->length - k - k;
        if (new_length > SIZE_MAX / sizeof(tuple->values[0])) {
            return false;
        }
    }

    for (size_t i = 0; i < list->count; ++i) {
        Tuple *tuple = &list->tuples[i];
        size_t new_length = tuple->length - k - k;

        if (new_length > 0) {
            memmove(tuple->values, tuple->values + k,
                    new_length * sizeof(tuple->values[0]));
        }

        tuple->length = new_length;
    }

    return true;
}

static bool print_tuple_list(const TupleList *list)
{
    if (list == NULL || (list->count > 0 && list->tuples == NULL)) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (size_t i = 0; i < list->count; ++i) {
        const Tuple *tuple = &list->tuples[i];

        if (tuple->length > 0 && tuple->values == NULL) {
            return false;
        }

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (putchar('(') == EOF) {
            return false;
        }

        for (size_t j = 0; j < tuple->length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (printf("%d", tuple->values[j]) < 0) {
                return false;
            }
        }

        if (tuple->length == 1 && putchar(',') == EOF) {
            return false;
        }

        if (putchar(')') == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    int values0[] = {5, 3, 1, 7, 4};
    int values1[] = {3, 3, 4, 2, 1, 4};
    int values2[] = {3, 7, 8, 2, 3};

    Tuple tuples[] = {
        {values0, sizeof(values0) / sizeof(values0[0])},
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])}
    };

    TupleList list = {
        tuples,
        sizeof(tuples) / sizeof(tuples[0])
    };

    const size_t k = 2;

    if (!trim_each_tuple_by_k(&list, k)) {
        fputs("Unable to trim the tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_tuple_list(&list)) {
        fputs("Unable to print the tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}