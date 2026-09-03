#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t used;
    size_t size;
} Set;

Set* create_set(size_t initial_size) {
    Set *set = (Set *)malloc(sizeof(Set));
    if (set == NULL) return NULL;
    set->elements = (int *)malloc(initial_size * sizeof(int));
    if (set->elements == NULL) {
        free(set);
        return NULL;
    }
    set->used = 0;
    set->size = initial_size;
    return set;
}

void destroy_set(Set *set) {
    if (set != NULL) {
        free(set->elements);
        free(set);
    }
}

int is_in_set(Set *set, int value) {
    for (size_t i = 0; i < set->used; ++i) {
        if (set->elements[i] == value) {
            return 1;
        }
    }
    return 0;
}

int add_to_set(Set *set, int value) {
    if (is_in_set(set, value)) return 0;
    if (set->used == set->size) {
        set->size *= 2;
        set->elements = (int *)realloc(set->elements, set->size * sizeof(int));
        if (set->elements == NULL) return -1;
    }
    set->elements[set->used++] = value;
    return 0;
}

Set* convert_tuples_to_set(const int tuples[], size_t length) {
    Set *set = create_set(length);
    if (set == NULL) return NULL;
    for (size_t i = 0; i < length; ++i) {
        if (add_to_set(set, tuples[i]) != 0) {
            destroy_set(set);
            return NULL;
        }
    }
    return set;
}

int main() {
    const int tuples[] = {1, 2, 3, 4, 5, 1, 2, 3};
    size_t length = sizeof(tuples) / sizeof(tuples[0]);
    Set *set = convert_tuples_to_set(tuples, length);
    if (set != NULL) {
        for (size_t i = 0; i < set->used; ++i) {
            printf("%d ", set->elements[i]);
        }
        printf("\n");
        destroy_set(set);
    } else {
        printf("Failed to create set\n");
    }
    return 0;
}