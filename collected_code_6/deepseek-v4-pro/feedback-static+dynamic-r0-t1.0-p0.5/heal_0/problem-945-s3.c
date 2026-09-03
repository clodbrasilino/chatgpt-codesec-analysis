#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} Set;

typedef struct {
    int *data;
    size_t length;
} Tuple;

void set_init(Set *set) {
    set->elements = NULL;
    set->size = 0;
    set->capacity = 0;
}

void set_destroy(Set *set) {
    free(set->elements);
    set->elements = NULL;
    set->size = 0;
    set->capacity = 0;
}

int set_contains(const Set *set, int value) {
    size_t i;
    for (i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            return 1;
        }
    }
    return 0;
}

int set_add(Set *set, int value) {
    if (set_contains(set, value)) {
        return 0;
    }
    
    if (set->size == set->capacity) {
        size_t new_capacity = set->capacity == 0 ? 8 : set->capacity * 2;
        int *new_elements = realloc(set->elements, new_capacity * sizeof(int));
        if (new_elements == NULL) {
            return -1;
        }
        set->elements = new_elements;
        set->capacity = new_capacity;
    }
    
    set->elements[set->size++] = value;
    return 1;
}

Set tuples_to_set(const Tuple *tuples, size_t tuple_count) {
    Set result;
    size_t i, j;
    
    set_init(&result);
    
    for (i = 0; i < tuple_count; i++) {
        for (j = 0; j < tuples[i].length; j++) {
            if (set_add(&result, tuples[i].data[j]) != 0) {
                set_destroy(&result);
                set_init(&result);
                return result;
            }
        }
    }
    
    return result;
}

void print_set(const Set *set) {
    size_t i;
    printf("{");
    for (i = 0; i < set->size; i++) {
        printf("%d", set->elements[i]);
        if (i < set->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void) {
    Tuple tuples[3];
    int data1[] = {1, 2, 3};
    int data2[] = {3, 4, 5};
    int data3[] = {5, 6, 7, 8};
    Set result;
    
    tuples[0].data = data1;
    tuples[0].length = 3;
    tuples[1].data = data2;
    tuples[1].length = 3;
    tuples[2].data = data3;
    tuples[2].length = 4;
    
    result = tuples_to_set(tuples, 3);
    print_set(&result);
    
    set_destroy(&result);
    
    return 0;
}