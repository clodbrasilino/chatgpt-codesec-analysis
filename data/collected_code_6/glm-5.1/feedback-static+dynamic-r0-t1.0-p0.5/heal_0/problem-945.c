#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple *items;
    size_t size;
    size_t capacity;
} TupleSet;

int tuple_equals(Tuple a, Tuple b) {
    return a.x == b.x && a.y == b.y;
}

int set_contains(TupleSet *set, Tuple t) {
    for (size_t i = 0; i < set->size; i++) {
        if (tuple_equals(set->items[i], t)) {
            return 1;
        }
    }
    return 0;
}

int set_add(TupleSet *set, Tuple t) {
    if (set_contains(set, t)) {
        return 0;
    }
    if (set->size == set->capacity) {
        size_t new_capacity = set->capacity == 0 ? 4 : set->capacity * 2;
        Tuple *new_items = realloc(set->items, new_capacity * sizeof(Tuple));
        if (!new_items) {
            return -1;
        }
        set->items = new_items;
        set->capacity = new_capacity;
    }
    set->items[set->size++] = t;
    return 1;
}

TupleSet tuples_to_set(Tuple *tuples, size_t tuple_count) {
    TupleSet set = {NULL, 0, 0};
    for (size_t i = 0; i < tuple_count; i++) {
        if (set_add(&set, tuples[i]) == -1) {
            free(set.items);
            set.items = NULL;
            set.size = 0;
            set.capacity = 0;
            return set;
        }
    }
    return set;
}

void free_set(TupleSet *set) {
    free(set->items);
    set->items = NULL;
    set->size = 0;
    set->capacity = 0;
}

int main(void) {
    Tuple tuples[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    TupleSet set = tuples_to_set(tuples, count);

    if (set.items == NULL && set.capacity > 0) {
        return 1;
    }

    for (size_t i = 0; i < set.size; i++) {
        printf("(%d, %d)\n", set.items[i].x, set.items[i].y);
    }

    free_set(&set);

    return 0;
}