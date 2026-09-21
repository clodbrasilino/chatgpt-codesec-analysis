#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

typedef struct {
    int *elements;
    size_t length;
} IntList;

static int resize_tuple_list(TupleList *list, size_t new_capacity) {
    Tuple *new_tuples;
    
    if (new_capacity == 0) {
        free(list->tuples);
        list->tuples = NULL;
        list->capacity = 0;
        list->count = 0;
        return 0;
    }
    
    if (new_capacity > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    
    new_tuples = (Tuple *)realloc(list->tuples, new_capacity * sizeof(Tuple));
    if (new_tuples == NULL) {
        return -1;
    }
    
    list->tuples = new_tuples;
    list->capacity = new_capacity;
    if (list->count > list->capacity) {
        list->count = list->capacity;
    }
    
    return 0;
}

static int add_tuple(TupleList *list, const Tuple *tuple) {
    size_t alloc_size;
    int *new_elements;
    
    if (list == NULL || tuple == NULL || tuple->elements == NULL || tuple->length == 0) {
        return -1;
    }
    
    if (list->count >= list->capacity) {
        size_t new_capacity;
        if (list->capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (resize_tuple_list(list, new_capacity) != 0) {
            return -1;
        }
    }
    
    if (tuple->length > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    alloc_size = tuple->length * sizeof(int);
    
    new_elements = (int *)malloc(alloc_size);
    if (new_elements == NULL) {
        return -1;
    }
    
    if (alloc_size > 0) {
        memcpy(new_elements, tuple->elements, alloc_size);
    }
    list->tuples[list->count].elements = new_elements;
    list->tuples[list->count].length = tuple->length;
    list->count++;
    
    return 0;
}

static void free_tuple_list(TupleList *list) {
    size_t i;
    
    if (list == NULL) {
        return;
    }
    
    for (i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
        list->tuples[i].elements = NULL;
        list->tuples[i].length = 0;
    }
    
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
    list->capacity = 0;
}

static TupleList *add_list_to_tuples(const IntList *list, const TupleList *tuples) {
    TupleList *result;
    size_t i;
    
    if (list == NULL || list->elements == NULL || list->length == 0 ||
        tuples == NULL || tuples->tuples == NULL || tuples->count == 0) {
        return NULL;
    }
    
    for (i = 0; i < tuples->count; i++) {
        if (tuples->tuples[i].elements == NULL || tuples->tuples[i].length == 0) {
            return NULL;
        }
    }
    
    result = (TupleList *)calloc(1, sizeof(TupleList));
    if (result == NULL) {
        return NULL;
    }
    
    if (tuples->count > SIZE_MAX / sizeof(Tuple)) {
        free(result);
        return NULL;
    }
    
    result->capacity = tuples->count;
    result->tuples = (Tuple *)calloc(result->capacity, sizeof(Tuple));
    if (result->tuples == NULL) {
        free(result);
        return NULL;
    }
    
    for (i = 0; i < tuples->count; i++) {
        size_t new_length;
        size_t total_size;
        size_t src1_size;
        size_t src2_size;
        size_t tuple_offset;
        int *new_elements;
        
        if (tuples->tuples[i].length > SIZE_MAX - list->length) {
            free_tuple_list(result);
            free(result);
            return NULL;
        }
        new_length = tuples->tuples[i].length + list->length;
        
        if (new_length > SIZE_MAX / sizeof(int)) {
            free_tuple_list(result);
            free(result);
            return NULL;
        }
        
        total_size = new_length * sizeof(int);
        
        new_elements = (int *)malloc(total_size);
        if (new_elements == NULL) {
            free_tuple_list(result);
            free(result);
            return NULL;
        }
        
        src1_size = tuples->tuples[i].length * sizeof(int);
        if (src1_size > total_size) {
            free(new_elements);
            free_tuple_list(result);
            free(result);
            return NULL;
        }
        
        memcpy(new_elements, tuples->tuples[i].elements, src1_size);
        
        src2_size = list->length * sizeof(int);
        tuple_offset = tuples->tuples[i].length * sizeof(int);
        
        if (tuple_offset > total_size || src2_size > total_size - tuple_offset) {
            free(new_elements);
            free_tuple_list(result);
            free(result);
            return NULL;
        }
        
        memcpy((unsigned char *)new_elements + tuple_offset, list->elements, src2_size);
        
        result->tuples[i].elements = new_elements;
        result->tuples[i].length = new_length;
        result->count++;
    }
    
    return result;
}

int main(void) {
    IntList list;
    TupleList input_tuples;
    TupleList *result;
    size_t i, j;
    
    int list_elements[] = {10, 20, 30};
    list.elements = list_elements;
    list.length = 3;
    
    int tuple1_elements[] = {1, 2, 3};
    int tuple2_elements[] = {4, 5};
    int tuple3_elements[] = {6, 7, 8, 9};
    
    Tuple tuples_array[3];
    
    tuples_array[0].elements = tuple1_elements;
    tuples_array[0].length = 3;
    
    tuples_array[1].elements = tuple2_elements;
    tuples_array[1].length = 2;
    
    tuples_array[2].elements = tuple3_elements;
    tuples_array[2].length = 4;
    
    input_tuples.tuples = tuples_array;
    input_tuples.count = 3;
    input_tuples.capacity = 3;
    
    result = add_list_to_tuples(&list, &input_tuples);
    
    if (result == NULL) {
        printf("Error: failed to add list to tuples\n");
        return 1;
    }
    
    for (i = 0; i < result->count; i++) {
        printf("Tuple %zu: ", i);
        for (j = 0; j < result->tuples[i].length; j++) {
            printf("%d ", result->tuples[i].elements[j]);
        }
        printf("\n");
    }
    
    free_tuple_list(result);
    free(result);
    
    return 0;
}