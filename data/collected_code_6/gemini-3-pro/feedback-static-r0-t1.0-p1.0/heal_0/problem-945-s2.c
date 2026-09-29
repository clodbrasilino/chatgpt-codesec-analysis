#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple* elements;
    size_t size;
    size_t capacity;
} Set;

Set* create_set(size_t capacity) {
    Set* set = (Set*)malloc(sizeof(Set));
    if (!set) {
        return NULL;
    }
    
    set->elements = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (!set->elements) {
        free(set);
        return NULL;
    }
    
    set->size = 0;
    set->capacity = capacity;
    return set;
}

void free_set(Set* set) {
    if (set) {
        free(set->elements);
        free(set);
    }
}

bool contains(Set* set, Tuple t) {
    if (!set) return false;
    for (size_t i = 0; i < set->size; i++) {
        if (set->elements[i].x == t.x && set->elements[i].y == t.y) {
            return true;
        }
    }
    return false;
}

bool add_to_set(Set* set, Tuple t) {
    if (!set || !set->elements) return false;
    
    if (contains(set, t)) {
        return true; 
    }
    
    if (set->size >= set->capacity) {
        size_t new_capacity = set->capacity == 0 ? 4 : set->capacity * 2;
        Tuple* new_elements = (Tuple*)realloc(set->elements, new_capacity * sizeof(Tuple));
        if (!new_elements) {
            return false;
        }
        set->elements = new_elements;
        set->capacity = new_capacity;
    }
    
    set->elements[set->size++] = t;
    return true;
}

Set* tuples_to_set(Tuple* tuples, size_t num_tuples) {
    if (!tuples) return NULL;
    
    Set* set = create_set(num_tuples);
    if (!set) return NULL;
    
    for (size_t i = 0; i < num_tuples; i++) {
        if (!add_to_set(set, tuples[i])) {
            free_set(set);
            return NULL;
        }
    }
    
    return set;
}

int main() {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    Set* set = tuples_to_set(tuples, num_tuples);
    if (!set) {
        fprintf(stderr, "Failed to create set.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < set->size; i++) {
        printf("(%d, %d)\n", set->elements[i].x, set->elements[i].y);
    }

    free_set(set);
    return EXIT_SUCCESS;
}