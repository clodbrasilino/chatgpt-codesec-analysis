#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int int_val;
        float float_val;
        char* string_val;
    } data;
} TupleElement;

typedef struct {
    TupleElement* elements;
    size_t size;
} Tuple;

void free_tuple(Tuple* tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->elements) {
        for (size_t i = 0; i < tuple->size; i++) {
            if (tuple->elements[i].type == TYPE_STRING && tuple->elements[i].data.string_val) {
                free(tuple->elements[i].data.string_val);
            }
        }
        free(tuple->elements);
    }
    free(tuple);
}

static char* safe_strdup(const char* src) {
    if (!src) {
        return NULL;
    }
    
    const char* p = src;
    while ((size_t)(p - src) < MAX_STRING_LEN && *p != '\0') {
        p++;
    }
    
    size_t len = (size_t)(p - src);
    char* dest = (char*)malloc(len + 1);
    
    if (dest) {
        for (size_t i = 0; i < len; i++) {
            dest[i] = src[i];
        }
        dest[len] = '\0';
    }
    
    return dest;
}

Tuple* remove_elements_by_type(const Tuple* input, DataType type_to_remove) {
    if (!input || !input->elements) {
        return NULL;
    }

    size_t new_size = 0;
    for (size_t i = 0; i < input->size; i++) {
        if (input->elements[i].type != type_to_remove) {
            new_size++;
        }
    }

    Tuple* new_tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!new_tuple) {
        return NULL;
    }

    new_tuple->size = new_size;
    new_tuple->elements = NULL;

    if (new_size > 0) {
        new_tuple->elements = (TupleElement*)malloc(new_size * sizeof(TupleElement));
        if (!new_tuple->elements) {
            free(new_tuple);
            return NULL;
        }

        size_t dest_idx = 0;
        for (size_t i = 0; i < input->size; i++) {
            if (input->elements[i].type != type_to_remove) {
                new_tuple->elements[dest_idx].type = input->elements[i].type;
                if (input->elements[i].type == TYPE_STRING) {
                    if (input->elements[i].data.string_val) {
                        new_tuple->elements[dest_idx].data.string_val = safe_strdup(input->elements[i].data.string_val);
                        if (!new_tuple->elements[dest_idx].data.string_val) {
                            new_tuple->size = dest_idx;
                            free_tuple(new_tuple);
                            return NULL;
                        }
                    } else {
                        new_tuple->elements[dest_idx].data.string_val = NULL;
                    }
                } else {
                    new_tuple->elements[dest_idx].data = input->elements[i].data;
                }
                dest_idx++;
            }
        }
    }

    return new_tuple;
}

int main(void) {
    Tuple* original = (Tuple*)malloc(sizeof(Tuple));
    if (!original) {
        return EXIT_FAILURE;
    }

    original->size = 4;
    original->elements = (TupleElement*)malloc(original->size * sizeof(TupleElement));
    if (!original->elements) {
        free(original);
        return EXIT_FAILURE;
    }

    original->elements[0].type = TYPE_INT;
    original->elements[0].data.int_val = 10;

    original->elements[1].type = TYPE_FLOAT;
    original->elements[1].data.float_val = 3.14f;

    original->elements[2].type = TYPE_STRING;
    const char* str = "Example";
    
    original->elements[2].data.string_val = safe_strdup(str);
    if (!original->elements[2].data.string_val) {
        original->size = 2;
        free_tuple(original);
        return EXIT_FAILURE;
    }

    original->elements[3].type = TYPE_INT;
    original->elements[3].data.int_val = 20;

    Tuple* filtered = remove_elements_by_type(original, TYPE_FLOAT);
    if (!filtered) {
        free_tuple(original);
        return EXIT_FAILURE;
    }

    free_tuple(original);
    free_tuple(filtered);

    return EXIT_SUCCESS;
}