#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleArray;

bool tuple_equals(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL) return false;
    return t1->a == t2->a && t1->b == t2->b;
}

bool init_tuple_array(TupleArray *arr, size_t initial_capacity) {
    if (arr == NULL) return false;
    if (initial_capacity > SIZE_MAX / sizeof(Tuple)) return false;
    arr->count = 0;
    arr->capacity = initial_capacity;
    if (initial_capacity == 0) {
        arr->items = NULL;
        return true;
    }
    arr->items = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (arr->items == NULL) return false;
    return true;
}

void free_tuple_array(TupleArray *arr) {
    if (arr == NULL) return;
    free(arr->items);
    arr->items = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

void remove_matching_tuples(TupleArray *arr1, const TupleArray *arr2) {
    if (arr1 == NULL || arr1->items == NULL) return;
    if (arr2 == NULL || arr2->items == NULL) return;
    
    size_t new_count = 0;
    for (size_t i = 0; i < arr1->count; i++) {
        bool matches = false;
        for (size_t j = 0; j < arr2->count; j++) {
            if (tuple_equals(&arr1->items[i], &arr2->items[j])) {
                matches = true;
                break;
            }
        }
        if (!matches) {
            arr1->items[new_count++] = arr1->items[i];
        }
    }
    arr1->count = new_count;
}

int main(void) {
    TupleArray arr1;
    TupleArray arr2;
    
    if (!init_tuple_array(&arr1, 4)) return EXIT_FAILURE;
    if (!init_tuple_array(&arr2, 2)) {
        free_tuple_array(&arr1);
        return EXIT_FAILURE;
    }
    
    arr1.items[0] = (Tuple){1, 2};
    arr1.items[1] = (Tuple){3, 4};
    arr1.items[2] = (Tuple){5, 6};
    arr1.items[3] = (Tuple){1, 2};
    arr1.count = 4;
    
    arr2.items[0] = (Tuple){1, 2};
    arr2.items[1] = (Tuple){7, 8};
    arr2.count = 2;
    
    remove_matching_tuples(&arr1, &arr2);
    
    for (size_t i = 0; i < arr1.count; i++) {
        printf("(%d, %d)\n", arr1.items[i].a, arr1.items[i].b);
    }
    
    free_tuple_array(&arr1);
    free_tuple_array(&arr2);
    
    return EXIT_SUCCESS;
}