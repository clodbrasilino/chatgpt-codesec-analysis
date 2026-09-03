#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_POINTER,
    TYPE_UNKNOWN
} DataType;

typedef struct {
    DataType type;
    void *data;
    size_t size;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
    size_t capacity;
} Tuple;

Tuple *tuple_create(void) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    tuple->elements = NULL;
    tuple->count = 0;
    tuple->capacity = 0;
    return tuple;
}

void tuple_destroy(Tuple *tuple) {
    if (!tuple) return;
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].data) {
            free(tuple->elements[i].data);
        }
    }
    free(tuple->elements);
    free(tuple);
}

int tuple_add(Tuple *tuple, DataType type, const void *data, size_t size) {
    if (!tuple || !data || size == 0) return -1;
    
    if (tuple->count >= tuple->capacity) {
        size_t new_capacity = tuple->capacity == 0 ? 4 : tuple->capacity * 2;
        TupleElement *new_elements = (TupleElement *)realloc(tuple->elements, new_capacity * sizeof(TupleElement));
        if (!new_elements) return -1;
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }
    
    tuple->elements[tuple->count].data = malloc(size);
    if (!tuple->elements[tuple->count].data) return -1;
    
    memcpy(tuple->elements[tuple->count].data, data, size);
    tuple->elements[tuple->count].type = type;
    tuple->elements[tuple->count].size = size;
    tuple->count++;
    
    return 0;
}

Tuple *tuple_remove_type(const Tuple *tuple, DataType type_to_remove) {
    if (!tuple) return NULL;
    
    Tuple *new_tuple = tuple_create();
    if (!new_tuple) return NULL;
    
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].type != type_to_remove) {
            if (tuple_add(new_tuple, tuple->elements[i].type, 
                         tuple->elements[i].data, tuple->elements[i].size) != 0) {
                tuple_destroy(new_tuple);
                return NULL;
            }
        }
    }
    
    return new_tuple;
}

void tuple_print(const Tuple *tuple) {
    if (!tuple) {
        printf("Empty tuple\n");
        return;
    }
    
    printf("Tuple contents (%zu elements):\n", tuple->count);
    for (size_t i = 0; i < tuple->count; i++) {
        printf("  [%zu] Type: ", i);
        switch (tuple->elements[i].type) {
            case TYPE_INT:
                printf("INT, Value: %d\n", *(int *)tuple->elements[i].data);
                break;
            case TYPE_FLOAT:
                printf("FLOAT, Value: %f\n", *(float *)tuple->elements[i].data);
                break;
            case TYPE_DOUBLE:
                printf("DOUBLE, Value: %lf\n", *(double *)tuple->elements[i].data);
                break;
            case TYPE_CHAR:
                printf("CHAR, Value: %c\n", *(char *)tuple->elements[i].data);
                break;
            case TYPE_STRING:
                printf("STRING, Value: %s\n", (char *)tuple->elements[i].data);
                break;
            case TYPE_POINTER:
                printf("POINTER, Value: %p\n", tuple->elements[i].data);
                break;
            default:
                printf("UNKNOWN\n");
                break;
        }
    }
}

int main(void) {
    Tuple *tuple = tuple_create();
    if (!tuple) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }
    
    int int_val1 = 42;
    int int_val2 = 100;
    float float_val = 3.14f;
    double double_val = 2.71828;
    char char_val = 'A';
    const char *str_val = "Hello";
    
    tuple_add(tuple, TYPE_INT, &int_val1, sizeof(int));
    tuple_add(tuple, TYPE_FLOAT, &float_val, sizeof(float));
    tuple_add(tuple, TYPE_INT, &int_val2, sizeof(int));
    tuple_add(tuple, TYPE_DOUBLE, &double_val, sizeof(double));
    tuple_add(tuple, TYPE_CHAR, &char_val, sizeof(char));
    tuple_add(tuple, TYPE_STRING, str_val, strlen(str_val) + 1);
    
    printf("Original tuple:\n");
    tuple_print(tuple);
    
    Tuple *filtered_tuple = tuple_remove_type(tuple, TYPE_INT);
    if (!filtered_tuple) {
        fprintf(stderr, "Failed to filter tuple\n");
        tuple_destroy(tuple);
        return 1;
    }
    
    printf("\nTuple after removing INT elements:\n");
    tuple_print(filtered_tuple);
    
    Tuple *filtered_tuple2 = tuple_remove_type(tuple, TYPE_STRING);
    if (!filtered_tuple2) {
        fprintf(stderr, "Failed to filter tuple\n");
        tuple_destroy(tuple);
        tuple_destroy(filtered_tuple);
        return 1;
    }
    
    printf("\nTuple after removing STRING elements:\n");
    tuple_print(filtered_tuple2);
    
    tuple_destroy(tuple);
    tuple_destroy(filtered_tuple);
    tuple_destroy(filtered_tuple2);
    
    return 0;
}