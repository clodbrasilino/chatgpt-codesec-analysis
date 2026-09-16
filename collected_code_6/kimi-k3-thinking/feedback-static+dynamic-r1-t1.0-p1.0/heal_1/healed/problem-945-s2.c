#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    size_t size;
    size_t capacity;
} TupleSet;

static int tuple_equals(Tuple a, Tuple b)
{
    return a.first == b.first && a.second == b.second;
}

static int set_init(TupleSet *set, size_t capacity)
{
    if (set == NULL) {
        return -1;
    }
    set->items = NULL;
    set->size = 0;
    set->capacity = 0;
    if (capacity == 0) {
        return 0;
    }
    set->items = malloc(capacity * sizeof(*set->items));
    if (set->items == NULL) {
        return -1;
    }
    set->capacity = capacity;
    return 0;
}

static int set_contains(const TupleSet *set, Tuple value)
{
    size_t i;
    if (set == NULL) {
        return 0;
    }
    for (i = 0; i < set->size; i++) {
        if (tuple_equals(set->items[i], value)) {
            return 1;
        }
    }
    return 0;
}

static int set_add(TupleSet *set, Tuple value)
{
    if (set == NULL) {
        return -1;
    }
    if (set_contains(set, value)) {
        return 0;
    }
    if (set->size == set->capacity) {
        size_t new_capacity = (set->capacity == 0) ? 8 : set->capacity * 2;
        Tuple *grown;
        if (new_capacity > SIZE_MAX / sizeof(*set->items)) {
            return -1;
        }
        grown = realloc(set->items, new_capacity * sizeof(*set->items));
        if (grown == NULL) {
            return -1;
        }
        set->items = grown;
        set->capacity = new_capacity;
    }
    set->items[set->size] = value;
    set->size++;
    return 0;
}

int tuples_to_set(const Tuple *tuples, size_t count, TupleSet *result)
{
    size_t i;

    if (result == NULL || (tuples == NULL && count > 0)) {
        return -1;
    }
    if (set_init(result, count) != 0) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        if (set_add(result, tuples[i]) != 0) {
            free(result->items);
            result->items = NULL;
            result->size = 0;
            result->capacity = 0;
            return -1;
        }
    }
    return 0;
}

void set_free(TupleSet *set)
{
    if (set == NULL) {
        return;
    }
    free(set->items);
    set->items = NULL;
    set->size = 0;
    set->capacity = 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4},
        {7, 8}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    TupleSet result;
    size_t i;

    if (tuples_to_set(tuples, count, &result) != 0) {
        fprintf(stderr, "Error: failed to convert tuples to set\n");
        return EXIT_FAILURE;
    }

    printf("Set contains %zu unique tuples:\n", result.size);
    for (i = 0; i < result.size; i++) {
        printf("(%d, %d)\n", result.items[i].first, result.items[i].second);
    }

    set_free(&result);
    return EXIT_SUCCESS;
}