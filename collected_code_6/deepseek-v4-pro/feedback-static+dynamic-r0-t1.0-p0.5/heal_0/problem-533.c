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
    void *data;
    DataType type;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
    size_t capacity;
} Tuple;

Tuple* create_tuple(size_t initial_capacity) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    
    tuple->elements = (TupleElement*)malloc(initial_capacity * sizeof(TupleElement));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = 0;
    tuple->capacity = initial_capacity;
    return tuple;
}

void destroy_tuple(Tuple *tuple) {
    if (!tuple) return;
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type == TYPE_STRING && tuple->elements[i].data) {
            free(tuple->elements[i].data);
        }
    }
    
    free(tuple->elements);
    free(tuple);
}

int tuple_add(Tuple *tuple, void *data, DataType type) {
    if (!tuple || !data) return -1;
    
    if (tuple->size >= tuple->capacity) {
        size_t new_capacity = tuple->capacity * 2;
        TupleElement *new_elements = (TupleElement*)realloc(tuple->elements, new_capacity * sizeof(TupleElement));
        if (!new_elements) return -1;
        
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }
    
    if (type == TYPE_STRING) {
        char *str = (char*)data;
        size_t len = strlen(str) + 1;
        char *str_copy = (char*)malloc(len);
        if (!str_copy) return -1;
        
        memcpy(str_copy, str, len);
        tuple->elements[tuple->size].data = str_copy;
    } else {
        tuple->elements[tuple->size].data = data;
    }
    
    tuple->elements[tuple->size].type = type;
    tuple->size++;
    
    return 0;
}

Tuple* remove_elements_by_type(Tuple *tuple, DataType type_to_remove) {
    if (!tuple) return NULL;
    
    Tuple *new_tuple = create_tuple(tuple->capacity);
    if (!new_tuple) return NULL;
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type != type_to_remove) {
            if (tuple_add(new_tuple, tuple->elements[i].data, tuple->elements[i].type) != 0) {
                destroy_tuple(new_tuple);
                return NULL;
            }
        }
    }
    
    return new_tuple;
}

void print_tuple(Tuple *tuple) {
    if (!tuple) return;
    
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        switch (tuple->elements[i].type) {
            case TYPE_INT:
                printf("%d", *(int*)tuple->elements[i].data);
                break;
            case TYPE_FLOAT:
                printf("%f", *(float*)tuple->elements[i].data);
                break;
            case TYPE_DOUBLE:
                printf("%lf", *(double*)tuple->elements[i].data);
                break;
            case TYPE_CHAR:
                printf("%c", *(char*)tuple->elements[i].data);
                break;
            case TYPE_STRING:
                printf("%s", (char*)tuple->elements[i].data);
                break;
            case TYPE_POINTER:
                printf("%p", tuple->elements[i].data);
                break;
            default:
                printf("unknown");
                break;
        }
        
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main() {
    Tuple *tuple = create_tuple(4);
    if (!tuple) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }
    
    int int_val1 = 10;
    int int_val2 = 20;
    float float_val = 3.14f;
    double double_val = 2.71828;
    char char_val = 'A';
    char *str_val = "hello";
    int *ptr_val = &int_val1;
    
    tuple_add(tuple, &int_val1, TYPE_INT);
    tuple_add(tuple, &float_val, TYPE_FLOAT);
    tuple_add(tuple, &double_val, TYPE_DOUBLE);
    tuple_add(tuple, &char_val, TYPE_CHAR);
    tuple_add(tuple, str_val, TYPE_STRING);
    tuple_add(tuple, &int_val2, TYPE_INT);
    tuple_add(tuple, ptr_val, TYPE_POINTER);
    
    printf("Original tuple: ");
    print_tuple(tuple);
    
    Tuple *filtered_tuple = remove_elements_by_type(tuple, TYPE_INT);
    if (filtered_tuple) {
        printf("Tuple after removing TYPE_INT elements: ");
        print_tuple(filtered_tuple);
        destroy_tuple(filtered_tuple);
    }
    
    filtered_tuple = remove_elements_by_type(tuple, TYPE_STRING);
    if (filtered_tuple) {
        printf("Tuple after removing TYPE_STRING elements: ");
        print_tuple(filtered_tuple);
        destroy_tuple(filtered_tuple);
    }
    
    filtered_tuple = remove_elements_by_type(tuple, TYPE_FLOAT);
    if (filtered_tuple) {
        printf("Tuple after removing TYPE_FLOAT elements: ");
        print_tuple(filtered_tuple);
        destroy_tuple(filtered_tuple);
    }
    
    destroy_tuple(tuple);
    
    return 0;
}