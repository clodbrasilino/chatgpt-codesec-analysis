#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} Set;

bool init_set(Set *set, size_t initial_capacity) {
    if (!set || initial_capacity == 0) {
        return false;
    }
    set->elements = (int *)malloc(initial_capacity * sizeof(int));
    if (!set->elements) {
        return false;
    }
    set->size = 0;
    set->capacity = initial_capacity;
    return true;
}

void free_set(Set *set) {
    if (set) {
        free(set->elements);
        set->elements = NULL;
        set->size = 0;
        set->capacity = 0;
    }
}

bool contains(const Set *set, int value) {
    if (!set || !set->elements) {
        return false;
    }
    for (size_t i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            return true;
        }
    }
    return false;
}

bool add_to_set(Set *set, int value) {
    if (!set) {
        return false;
    }
    if (contains(set, value)) {
        return true;
    }
    if (set->size >= set->capacity) {
        size_t new_capacity = set->capacity * 2;
        int *new_elements = (int *)realloc(set->elements, new_capacity * sizeof(int));
        if (!new_elements) {
            return false;
        }
        set->elements = new_elements;
        set->capacity = new_capacity;
    }
    set->elements[set->size++] = value;
    return true;
}

bool tuples_to_set(int **tuples, size_t num_tuples, size_t tuple_size, Set *out_set) {
    if (!tuples || !out_set) {
        return false;
    }
    for (size_t i = 0; i < num_tuples; i++) {
        if (!tuples[i]) {
            return false;
        }
        for (size_t j = 0; j < tuple_size; j++) {
            if (!add_to_set(out_set, tuples[i][j])) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {3, 4, 5};
    int tuple3[] = {5, 6, 1};
    
    int *tuples[] = {tuple1, tuple2, tuple3};
    size_t num_tuples = 3;
    size_t tuple_size = 3;

    Set my_set;
    if (!init_set(&my_set, 4)) {
        fprintf(stderr, "Failed to initialize set\n");
        return EXIT_FAILURE;
    }

    if (!tuples_to_set(tuples, num_tuples, tuple_size, &my_set)) {
        fprintf(stderr, "Failed to convert tuples to set\n");
        free_set(&my_set);
        return EXIT_FAILURE;
    }

    printf("Set elements: ");
    for (size_t i = 0; i < my_set.size; i++) {
        printf("%d ", my_set.elements[i]);
    }
    printf("\n");

    free_set(&my_set);
    return EXIT_SUCCESS;
}