#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
    size_t capacity;
} Set;

Set* create_set(size_t initial_capacity) {
    Set *set = (Set*)malloc(sizeof(Set));
    if (set == NULL) return NULL;
    set->elements = (int*)malloc(initial_capacity * sizeof(int));
    if (set->elements == NULL) {
        free(set);
        return NULL;
    }
    set->count = 0;
    set->capacity = initial_capacity;
    return set;
}

void destroy_set(Set *set) {
    if (set != NULL) {
        free(set->elements);
        free(set);
    }
}

int contains(Set *set, int value) {
    for (size_t i = 0; i < set->count; ++i) {
        if (set->elements[i] == value) {
            return 1;
        }
    }
    return 0;
}

int add_to_set(Set *set, int value) {
    if (contains(set, value)) return 0;
    if (set->count >= set->capacity) {
        set->capacity *= 2;
        set->elements = (int*)realloc(set->elements, set->capacity * sizeof(int));
        if (set->elements == NULL) return -1;
    }
    set->elements[set->count++] = value;
    return 1;
}

Set* tuples_to_set(int *tuples, size_t length) {
    Set *set = create_set(length);
    if (set == NULL) return NULL;
    for (size_t i = 0; i < length; ++i) {
        if (add_to_set(set, tuples[i]) == -1) {
            destroy_set(set);
            return NULL;
        }
    }
    return set;
}

void print_set(Set *set) {
    printf("{ ");
    for (size_t i = 0; i < set->count; ++i) {
        printf("%d ", set->elements[i]);
    }
    printf("}\n");
}

int main() {
    int tuples[] = {1, 2, 3, 4, 5, 2, 3, 6, 7, 8, 9, 1};
    size_t length = sizeof(tuples) / sizeof(tuples[0]);
    Set *set = tuples_to_set(tuples, length);
    if (set != NULL) {
        print_set(set);
        destroy_set(set);
    }
    return 0;
}