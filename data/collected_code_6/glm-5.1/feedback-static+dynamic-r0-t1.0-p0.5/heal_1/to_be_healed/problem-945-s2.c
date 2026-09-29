#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} Set;

Set *set_create(size_t initial_capacity) {
    Set *set = (Set *)malloc(sizeof(Set));
    if (!set) return NULL;
    set->elements = (int *)malloc(initial_capacity * sizeof(int));
    if (!set->elements) {
        free(set);
        return NULL;
    }
    set->size = 0;
    set->capacity = initial_capacity;
    return set;
}

void set_free(Set *set) {
    if (set) {
        free(set->elements);
        free(set);
    }
}

int set_contains(Set *set, int value) {
    for (size_t i = 0; i < set->size; i++) {
        if (set->elements[i] == value) return 1;
    }
    return 0;
}

int set_add(Set *set, int value) {
    if (set_contains(set, value)) return 0;
    if (set->size == set->capacity) {
        size_t new_capacity = set->capacity * 2;
        int *new_elements = (int *)realloc(set->elements, new_capacity * sizeof(int));
        if (!new_elements) return -1;
        set->elements = new_elements;
        set->capacity = new_capacity;
    }
    set->elements[set->size++] = value;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
Set *tuples_to_set(int *tuples, size_t tuple_count, size_t tuple_size) {
    Set *set = set_create(tuple_count * tuple_size);
    if (!set) return NULL;
    for (size_t i = 0; i < tuple_count; i++) {
        for (size_t j = 0; j < tuple_size; j++) {
            if (set_add(set, tuples[i * tuple_size + j]) == -1) {
                set_free(set);
                return NULL;
            }
        }
    }
    return set;
}

int main(void) {
    int data[][3] = {{1, 2, 3}, {2, 3, 4}, {4, 5, 6}, {1, 2, 3}};
    size_t tuple_count = sizeof(data) / sizeof(data[0]);
    size_t tuple_size = sizeof(data[0]) / sizeof(data[0][0]);
    
    Set *set = tuples_to_set((int *)data, tuple_count, tuple_size);
    if (!set) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < set->size; i++) {
        printf("%d ", set->elements[i]);
    }
    printf("\n");
    
    set_free(set);
    return EXIT_SUCCESS;
}