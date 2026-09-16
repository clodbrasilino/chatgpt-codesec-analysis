#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    size_t size;
} TupleSet;

static bool tuple_equals(const Tuple *left, const Tuple *right)
{
    return left->first == right->first && left->second == right->second;
}

static void tuple_set_destroy(TupleSet *set)
{
    if (set != NULL) {
        free(set->items);
        set->items = NULL;
        set->size = 0;
        free(set);
    }
}

static TupleSet *tuples_to_set(const Tuple *tuples, size_t tuple_count)
{
    TupleSet *set = calloc(1, sizeof(*set));

    if (set == NULL) {
        return NULL;
    }

    if (tuple_count == 0) {
        return set;
    }

    if (tuples == NULL || tuple_count > SIZE_MAX / sizeof(*set->items)) {
        tuple_set_destroy(set);
        return NULL;
    }

    set->items = malloc(tuple_count * sizeof(*set->items));
    if (set->items == NULL) {
        tuple_set_destroy(set);
        return NULL;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        bool exists = false;

        for (size_t j = 0; j < set->size; ++j) {
            if (tuple_equals(&tuples[i], &set->items[j])) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            set->items[set->size++] = tuples[i];
        }
    }

    return set;
}

static bool print_tuple_set(const TupleSet *set)
{
    if (set == NULL || printf("{") < 0) {
        return false;
    }

    for (size_t i = 0; i < set->size; ++i) {
        if (i > 0 && printf(", ") < 0) {
            return false;
        }

        if (printf("(%d, %d)", set->items[i].first,
                   set->items[i].second) < 0) {
            return false;
        }
    }

    return printf("}\n") >= 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    TupleSet *set = tuples_to_set(tuples, tuple_count);

    if (set == NULL) {
        return EXIT_FAILURE;
    }

    if (!print_tuple_set(set) || fflush(stdout) == EOF) {
        tuple_set_destroy(set);
        return EXIT_FAILURE;
    }

    tuple_set_destroy(set);
    return EXIT_SUCCESS;
}