#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_UNKNOWN
} DataType;

typedef struct {
    DataType type;
    void *data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
} Tuple;

bool check_same_type(const Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size == 0) {
        return false;
    }
    
    if (tuple->size == 1) {
        return true;
    }
    
    DataType first_type = tuple->elements[0].type;
    
    for (size_t i = 1; i < tuple->size; i++) {
        if (tuple->elements[i].type != first_type) {
            return false;
        }
    }
    
    return true;
}

Tuple* create_tuple(size_t size) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = (TupleElement*)calloc(size, sizeof(TupleElement));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        if (tuple->elements != NULL) {
            for (size_t i = 0; i < tuple->size; i++) {
                if (tuple->elements[i].type == TYPE_STRING && 
                    tuple->elements[i].data != NULL) {
                    free(tuple->elements[i].data);
                }
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

bool set_int_element(Tuple *tuple, size_t index, int value) {
    if (tuple == NULL || index >= tuple->size) {
        return false;
    }
    
    int *data = (int*)malloc(sizeof(int));
    if (data == NULL) {
        return false;
    }
    
    *data = value;
    tuple->elements[index].type = TYPE_INT;
    tuple->elements[index].data = data;
    return true;
}

bool set_float_element(Tuple *tuple, size_t index, float value) {
    if (tuple == NULL || index >= tuple->size) {
        return false;
    }
    
    float *data = (float*)malloc(sizeof(float));
    if (data == NULL) {
        return false;
    }
    
    *data = value;
    tuple->elements[index].type = TYPE_FLOAT;
    tuple->elements[index].data = data;
    return true;
}

bool set_string_element(Tuple *tuple, size_t index, const char *value) {
    if (tuple == NULL || index >= tuple->size || value == NULL) {
        return false;
    }
    
    size_t len = strlen(value);
    char *data = (char*)malloc(len + 1);
    if (data == NULL) {
        return false;
    }
    
    strcpy(data, value);
    tuple->elements[index].type = TYPE_STRING;
    tuple->elements[index].data = data;
    return true;
}

int main(void) {
    Tuple *tuple1 = create_tuple(3);
    if (tuple1 == NULL) {
        fprintf(stderr, "Failed to create tuple1\n");
        return EXIT_FAILURE;
    }
    
    if (!set_int_element(tuple1, 0, 10) ||
        !set_int_element(tuple1, 1, 20) ||
        !set_int_element(tuple1, 2, 30)) {
        fprintf(stderr, "Failed to set elements in tuple1\n");
        free_tuple(tuple1);
        return EXIT_FAILURE;
    }
    
    printf("Tuple1 (all integers): %s\n", 
           check_same_type(tuple1) ? "Same type" : "Different types");
    
    Tuple *tuple2 = create_tuple(3);
    if (tuple2 == NULL) {
        fprintf(stderr, "Failed to create tuple2\n");
        free_tuple(tuple1);
        return EXIT_FAILURE;
    }
    
    if (!set_int_element(tuple2, 0, 10) ||
        !set_float_element(tuple2, 1, 3.14f) ||
        !set_string_element(tuple2, 2, "hello")) {
        fprintf(stderr, "Failed to set elements in tuple2\n");
        free_tuple(tuple1);
        free_tuple(tuple2);
        return EXIT_FAILURE;
    }
    
    printf("Tuple2 (mixed types): %s\n", 
           check_same_type(tuple2) ? "Same type" : "Different types");
    
    Tuple *tuple3 = create_tuple(2);
    if (tuple3 == NULL) {
        fprintf(stderr, "Failed to create tuple3\n");
        free_tuple(tuple1);
        free_tuple(tuple2);
        return EXIT_FAILURE;
    }
    
    if (!set_string_element(tuple3, 0, "world") ||
        !set_string_element(tuple3, 1, "test")) {
        fprintf(stderr, "Failed to set elements in tuple3\n");
        free_tuple(tuple1);
        free_tuple(tuple2);
        free_tuple(tuple3);
        return EXIT_FAILURE;
    }
    
    printf("Tuple3 (all strings): %s\n", 
           check_same_type(tuple3) ? "Same type" : "Different types");
    
    free_tuple(tuple1);
    free_tuple(tuple2);
    free_tuple(tuple3);
    
    return EXIT_SUCCESS;
}