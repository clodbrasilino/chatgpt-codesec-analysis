#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t used;
    size_t size;
} Set;

Set* create_set(size_t initial_size) {
    Set *set = (Set*)malloc(sizeof(Set));
    if (!set) return NULL;
    set->elements = (int*)malloc(initial_size * sizeof(int));
    if (!set->elements) {
        free(set);
        return NULL;
    }
    set->used = 0;
    set->size = initial_size;
    return set;
}

void destroy_set(Set *set) {
    if (set) {
        free(set->elements);
        free(set);
    }
}

int add_to_set(Set *set, int element) {
    for (size_t i = 0; i < set->used; ++i) {
        if (set->elements[i] == element) return 0;
    }
    if (set->used == set->size) {
        set->size *= 2;
        set->elements = (int*)realloc(set->elements, set->size * sizeof(int));
        if (!set->elements) return -1;
    }
    set->elements[set->used++] = element;
    return 1;
}

Set* tuples_to_set(const int *tuples, size_t count) {
    Set *set = create_set(count);
    if (!set) return NULL;
    for (size_t i = 0; i < count; ++i) {
        if (add_to_set(set, tuples[i]) < 0) {
            destroy_set(set);
            return NULL;
        }
    }
    return set;
}

int main() {
    int tuples[] = {1, 2, 3, 4, 5, 1, 2, 3};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    Set *set = tuples_to_set(tuples, count);
    if (set) {
        for (size_t i = 0; i < set->used; ++i) {
            printf("%d ", set->elements[i]);
        }
        printf("\n");
        destroy_set(set);
    }
    return 0;
}