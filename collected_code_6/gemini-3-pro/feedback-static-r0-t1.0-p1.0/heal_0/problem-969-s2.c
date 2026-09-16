#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int value1;
    int value2;
} Tuple;

typedef struct {
    Tuple* array;
    size_t size;
    size_t capacity;
} TupleArray;

TupleArray* create_tuple_array(size_t capacity) {
    TupleArray* arr = (TupleArray*)malloc(sizeof(TupleArray));
    if (!arr) return NULL;
    
    arr->array = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (!arr->array) {
        free(arr);
        return NULL;
    }
    
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

int add_tuple(TupleArray* arr, Tuple t) {
    if (!arr) return -1;
    
    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * 2;
        Tuple* new_array = (Tuple*)realloc(arr->array, new_capacity * sizeof(Tuple));
        if (!new_array) return -1;
        arr->array = new_array;
        arr->capacity = new_capacity;
    }
    
    arr->array[arr->size++] = t;
    return 0;
}

void free_tuple_array(TupleArray* arr) {
    if (arr) {
        free(arr->array);
        free(arr);
    }
}

TupleArray* join_tuples(const TupleArray* input) {
    if (!input) return NULL;
    
    TupleArray* result = create_tuple_array(input->size);
    if (!result) return NULL;
    
    for (size_t i = 0; i < input->size; i++) {
        int found = 0;
        for (size_t j = 0; j < result->size; j++) {
            if (result->array[j].id == input->array[i].id) {
                result->array[j].value1 += input->array[i].value1;
                result->array[j].value2 += input->array[i].value2;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (add_tuple(result, input->array[i]) != 0) {
                free_tuple_array(result);
                return NULL;
            }
        }
    }
    
    return result;
}

int main() {
    TupleArray* input = create_tuple_array(5);
    if (!input) return EXIT_FAILURE;
    
    Tuple t1 = {1, 10, 20};
    Tuple t2 = {2, 15, 25};
    Tuple t3 = {1, 5, 10};
    Tuple t4 = {3, 30, 40};
    Tuple t5 = {2, 5, 5};
    
    if (add_tuple(input, t1) != 0 ||
        add_tuple(input, t2) != 0 ||
        add_tuple(input, t3) != 0 ||
        add_tuple(input, t4) != 0 ||
        add_tuple(input, t5) != 0) {
        free_tuple_array(input);
        return EXIT_FAILURE;
    }
    
    TupleArray* result = join_tuples(input);
    if (!result) {
        free_tuple_array(input);
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < result->size; i++) {
        printf("{id: %d, val1: %d, val2: %d}\n", 
               result->array[i].id, 
               result->array[i].value1, 
               result->array[i].value2);
    }
    
    free_tuple_array(input);
    free_tuple_array(result);
    
    return EXIT_SUCCESS;
}