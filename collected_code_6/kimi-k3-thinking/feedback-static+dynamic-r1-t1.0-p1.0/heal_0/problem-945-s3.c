#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *elements;
    size_t size;
    size_t capacity;
} TupleSet;

static bool tuple_equals(const Tuple *a, const Tuple *b)
{
    if (a == NULL || b == NULL) {
        return false;
    }
    return (a->first == b->first) && (a->second == b->second);
}

static bool set_contains(const TupleSet *set, const Tuple *tuple)
{
    size_t i;

    if (set == NULL || tuple == NULL || set->elements == NULL) {
        return false;
    }

    for (i = 0; i < set->size; i++) {
        if (tuple_equals(&set->elements[i], tuple)) {
            return true;
        }
    }
    return false;
}

TupleSet *tuples_to_set(const Tuple *tuples, size_t count)
{
    TupleSet *set;
    size_t i;

    if (tuples == NULL || count == 0) {
        return NULL;
    }

    set = (TupleSet *)malloc(sizeof(TupleSet));
    if (set == NULL) {
        return NULL;
    }

    set->elements = (Tuple *)malloc(count * sizeof(Tuple));
    if (set->elements == NULL) {
        free(set);
        return NULL;
    }

    set->size = 0;
    set->capacity = count;

    for (i = 0; i < count; i++) {
        if (!set_contains(set, &tuples[i])) {
            set->elements[set->size] = tuples[i];
            set->size++;
        }
    }

    return set;
}

void free_set(TupleSet *set)
{
    if (set != NULL) {
        free(set->elements);
        set->elements = NULL;
        free(set);
    }
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
    TupleSet *set;
    size_t i;

    set = tuples_to_set(tuples, count);
    if (set == NULL) {
        fprintf(stderr, "Error: failed to convert tuples to set\n");
        return EXIT_FAILURE;
    }

    printf("Set contains %zu unique tuples:\n", set->size);
    for (i = 0; i < set->size; i++) {
        printf("(%d, %d)\n", set->elements[i].first, set->elements[i].second);
    }

    free_set(set);
    set = NULL;

    return EXIT_SUCCESS;
}