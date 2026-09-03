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
    TYPE_LONG,
    TYPE_SHORT,
    TYPE_UNSIGNED
} DataType;

typedef struct {
    DataType type;
    void *data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
    size_t capacity;
} Tuple;

Tuple *create_tuple(void) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->elements = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
    return tuple;
}

int tuple_add_element(Tuple *tuple, DataType type, void *data) {
    if (tuple == NULL || data == NULL) {
        return -1;
    }
    
    if (tuple->size >= tuple->capacity) {
        size_t new_capacity = (tuple->capacity == 0) ? 4 : tuple->capacity * 2;
        TupleElement *new_elements = (TupleElement *)realloc(tuple->elements, new_capacity * sizeof(TupleElement));
        if (new_elements == NULL) {
            return -1;
        }
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }
    
    tuple->elements[tuple->size].type = type;
    tuple->elements[tuple->size].data = data;
    tuple->size++;
    return 0;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    free(tuple->elements);
    free(tuple);
}

Tuple *remove_elements_by_type(Tuple *tuple, DataType type_to_remove) {
    if (tuple == NULL) {
        return NULL;
    }
    
    Tuple *new_tuple = create_tuple();
    if (new_tuple == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type != type_to_remove) {
            if (tuple_add_element(new_tuple, tuple->elements[i].type, tuple->elements[i].data) != 0) {
                free_tuple(new_tuple);
                return NULL;
            }
        }
    }
    
    return new_tuple;
}

void print_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        printf("NULL tuple\n");
        return;
    }
    
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        switch (tuple->elements[i].type) {
            case TYPE_INT:
                printf("%d", *(int *)tuple->elements[i].data);
                break;
            case TYPE_FLOAT:
                printf("%f", *(float *)tuple->elements[i].data);
                break;
            case TYPE_DOUBLE:
                printf("%lf", *(double *)tuple->elements[i].data);
                break;
            case TYPE_CHAR:
                printf("%c", *(char *)tuple->elements[i].data);
                break;
            case TYPE_STRING:
                printf("%s", (char *)tuple->elements[i].data);
                break;
            case TYPE_LONG:
                printf("%ld", *(long *)tuple->elements[i].data);
                break;
            case TYPE_SHORT:
                printf("%d", *(short *)tuple->elements[i].data);
                break;
            case TYPE_UNSIGNED:
                printf("%u", *(unsigned int *)tuple->elements[i].data);
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

int main(void) {
    Tuple *tuple = create_tuple();
    if (tuple == NULL) {
        return 1;
    }
    
    int int_val1 = 10;
    int int_val2 = 20;
    float float_val = 3.14f;
    double double_val = 2.71828;
    char char_val = 'A';
    char *string_val = "hello";
    long long_val = 123456789L;
    short short_val = 100;
    unsigned int uint_val = 42;
    
    tuple_add_element(tuple, TYPE_INT, &int_val1);
    tuple_add_element(tuple, TYPE_FLOAT, &float_val);
    tuple_add_element(tuple, TYPE_INT, &int_val2);
    tuple_add_element(tuple, TYPE_DOUBLE, &double_val);
    tuple_add_element(tuple, TYPE_CHAR, &char_val);
    tuple_add_element(tuple, TYPE_STRING, string_val);
    tuple_add_element(tuple, TYPE_LONG, &long_val);
    tuple_add_element(tuple, TYPE_SHORT, &short_val);
    tuple_add_element(tuple, TYPE_UNSIGNED, &uint_val);
    
    printf("Original tuple: ");
    print_tuple(tuple);
    
    Tuple *filtered_tuple = remove_elements_by_type(tuple, TYPE_INT);
    if (filtered_tuple == NULL) {
        free_tuple(tuple);
        return 1;
    }
    
    printf("Tuple after removing TYPE_INT elements: ");
    print_tuple(filtered_tuple);
    
    Tuple *filtered_tuple2 = remove_elements_by_type(tuple, TYPE_STRING);
    if (filtered_tuple2 == NULL) {
        free_tuple(tuple);
        free_tuple(filtered_tuple);
        return 1;
    }
    
    printf("Tuple after removing TYPE_STRING elements: ");
    print_tuple(filtered_tuple2);
    
    free_tuple(tuple);
    free_tuple(filtered_tuple);
    free_tuple(filtered_tuple2);
    
    return 0;
}