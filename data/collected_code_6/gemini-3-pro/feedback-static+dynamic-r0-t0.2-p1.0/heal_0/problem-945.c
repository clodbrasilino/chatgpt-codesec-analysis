#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} Set;

Set* create_set(size_t initial_capacity) {
    Set *set = (Set*)malloc(sizeof(Set));
    if (!set) {
        return NULL;
    }
    set->elements = (int*)malloc(initial_capacity * sizeof(int));
    if (!set->elements) {
        free(set);
        return NULL;
    }
    set->size = 0;
    set->capacity = initial_capacity;
    return set;
}

void free_set(Set *set) {
    if (set) {
        free(set->elements);
        free(set);
    }
}

bool set_contains(const Set *set, int value) {
    if (!set) return false;
    for (size_t i = 0; i < set->size; ++i) {
        if (set->elements[i] == value) {
            return true;
        }
    }
    return false;
}

bool set_add(Set *set, int value) {
    if (!set) return false;
    if (set_contains(set, value)) {
        return true;
    }
    if (set->size == set->capacity) {
        size_t new_capacity = set->capacity == 0 ? 4 : set->capacity * 2;
        int *new_elements = (int*)realloc(set->elements, new_capacity * sizeof(int));
        if (!new_elements) {
            return false;
        }
        set->elements = new_elements;
        set->capacity = new_capacity;
    }
    set->elements[set->size++] = value;
    return true;
}

Set* tuples_to_set(const int *tuples, size_t num_elements) {
    if (!tuples) return NULL;
    Set *set = create_set(num_elements);
    if (!set) return NULL;
    
    for (size_t i = 0; i < num_elements; ++i) {
        if (!set_add(set, tuples[i])) {
            free_set(set);
            return NULL;
        }
    }
    return set;
}

int main(void) {
    int tuples[] = {1, 2, 2, 3, 4, 4, 5, 1};
    size_t num_elements = sizeof(tuples) / sizeof(tuples[0]);
    
    Set *my_set = tuples_to_set(tuples, num_elements);
    if (!my_set) {
        fprintf(stderr, "Failed to create set.\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < my_set->size; ++i) {
        printf("%d ", my_set->elements[i]);
    }
    printf("\n");
    
    free_set(my_set);
    return EXIT_SUCCESS;
}