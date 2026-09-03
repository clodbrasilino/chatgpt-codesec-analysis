#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    size_t size;
    size_t capacity;
} TupleSet;

int tuple_equal(Tuple a, Tuple b) {
    return a.first == b.first && a.second == b.second;
}

int tuple_set_init(TupleSet *set, size_t capacity) {
    set->items = NULL;
    set->size = 0;
    set->capacity = 0;

    set->items = malloc(capacity * sizeof(Tuple));
    if (set->items == NULL) {
        return 0;
    }

    set->capacity = capacity;
    return 1;
}

void tuple_set_free(TupleSet *set) {
    free(set->items);
    set->items = NULL;
    set->size = 0;
    set->capacity = 0;
}

int tuple_set_contains(const TupleSet *set, Tuple tuple) {
    size_t i;

    for (i = 0; i < set->size; i++) {
        if (tuple_equal(set->items[i], tuple)) {
            return 1;
        }
    }

    return 0;
}

int tuple_set_add(TupleSet *set, Tuple tuple) {
    Tuple *new_items;
    size_t new_capacity;

    if (tuple_set_contains(set, tuple)) {
        return 1;
    }

    if (set->size == set->capacity) {
        new_capacity = set->capacity == 0 ? 1 : set->capacity * 2;
        new_items = realloc(set->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            return 0;
        }
        set->items = new_items;
        set->capacity = new_capacity;
    }

    set->items[set->size] = tuple;
    set->size++;
    return 1;
}

TupleSet tuples_to_set(const Tuple *tuples, size_t count) {
    TupleSet set;
    size_t i;

    if (!tuple_set_init(&set, count > 0 ? count : 1)) {
        return set;
    }

    for (i = 0; i < count; i++) {
        if (!tuple_set_add(&set, tuples[i])) {
            tuple_set_free(&set);
            return set;
        }
    }

    return set;
}

int main(void) {
    Tuple input[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4}
    };
    size_t input_size = sizeof(input) / sizeof(input[0]);
    TupleSet set;
    size_t i;

    set = tuples_to_set(input, input_size);
    if (set.items == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < set.size; i++) {
        printf("(%d, %d)\n", set.items[i].first, set.items[i].second);
    }

    tuple_set_free(&set);
    return EXIT_SUCCESS;
}