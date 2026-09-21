#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 4096

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} ElementType;

typedef union {
    int i_val;
    float f_val;
    char* s_val;
} ElementData;

typedef struct {
    ElementType type;
    ElementData data;
} TupleElement;

typedef struct {
    TupleElement* elements;
    size_t size;
    size_t capacity;
} Tuple;

Tuple* create_tuple(size_t initial_capacity) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    
    if (initial_capacity > 0) {
        tuple->elements = (TupleElement*)malloc(initial_capacity * sizeof(TupleElement));
        if (!tuple->elements) {
            free(tuple);
            return NULL;
        }
    } else {
        tuple->elements = NULL;
    }
    
    tuple->size = 0;
    tuple->capacity = initial_capacity;
    return tuple;
}

void destroy_tuple(Tuple* tuple) {
    if (!tuple) {
        return;
    }
    
    if (tuple->elements) {
        for (size_t i = 0; i < tuple->size; i++) {
            if (tuple->elements[i].type == TYPE_STRING && tuple->elements[i].data.s_val) {
                free(tuple->elements[i].data.s_val);
            }
        }
        free(tuple->elements);
    }
    free(tuple);
}

static int ensure_capacity(Tuple* tuple) {
    if (!tuple) {
        return -1;
    }
    
    if (tuple->size >= tuple->capacity) {
        size_t new_capacity = tuple->capacity == 0 ? 4 : tuple->capacity * 2;
        TupleElement* new_elements = (TupleElement*)realloc(tuple->elements, new_capacity * sizeof(TupleElement));
        if (!new_elements) {
            return -1;
        }
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }
    return 0;
}

int add_int(Tuple* tuple, int value) {
    if (ensure_capacity(tuple) != 0) {
        return -1;
    }
    
    tuple->elements[tuple->size].type = TYPE_INT;
    tuple->elements[tuple->size].data.i_val = value;
    tuple->size++;
    return 0;
}

int add_float(Tuple* tuple, float value) {
    if (ensure_capacity(tuple) != 0) {
        return -1;
    }
    
    tuple->elements[tuple->size].type = TYPE_FLOAT;
    tuple->elements[tuple->size].data.f_val = value;
    tuple->size++;
    return 0;
}

int add_string(Tuple* tuple, const char* value) {
    if (!value || ensure_capacity(tuple) != 0) {
        return -1;
    }
    
    size_t len = 0;
    while (value[len] != '\0' && len < MAX_STRING_LEN) {
        len++;
    }
    
    char* copy = (char*)malloc(len + 1);
    if (!copy) {
        return -1;
    }
    
    for (size_t i = 0; i < len; i++) {
        copy[i] = value[i];
    }
    copy[len] = '\0';
    
    tuple->elements[tuple->size].type = TYPE_STRING;
    tuple->elements[tuple->size].data.s_val = copy;
    tuple->size++;
    return 0;
}

int remove_elements_by_type(Tuple* tuple, ElementType target_type) {
    if (!tuple || !tuple->elements) {
        return -1;
    }
    
    size_t write_index = 0;
    
    for (size_t read_index = 0; read_index < tuple->size; read_index++) {
        if (tuple->elements[read_index].type == target_type) {
            if (target_type == TYPE_STRING && tuple->elements[read_index].data.s_val) {
                free(tuple->elements[read_index].data.s_val);
                tuple->elements[read_index].data.s_val = NULL;
            }
        } else {
            if (write_index != read_index) {
                tuple->elements[write_index] = tuple->elements[read_index];
            }
            write_index++;
        }
    }
    
    tuple->size = write_index;
    return 0;
}

int main(void) {
    Tuple* tuple = create_tuple(4);
    if (!tuple) {
        return EXIT_FAILURE;
    }

    if (add_int(tuple, 10) != 0) goto cleanup;
    if (add_string(tuple, "Remove Me") != 0) goto cleanup;
    if (add_float(tuple, 3.14f) != 0) goto cleanup;
    if (add_string(tuple, "Also Remove Me") != 0) goto cleanup;
    if (add_int(tuple, 20) != 0) goto cleanup;

    if (remove_elements_by_type(tuple, TYPE_STRING) != 0) {
        goto cleanup;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type == TYPE_INT) {
            printf("Integer: %d\n", tuple->elements[i].data.i_val);
        } else if (tuple->elements[i].type == TYPE_FLOAT) {
            printf("Float: %.2f\n", tuple->elements[i].data.f_val);
        } else if (tuple->elements[i].type == TYPE_STRING) {
            printf("String: %s\n", tuple->elements[i].data.s_val);
        }
    }

cleanup:
    destroy_tuple(tuple);
    return EXIT_SUCCESS;
}