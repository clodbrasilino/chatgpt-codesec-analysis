#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#define MAX_TUPLE_SIZE 1024

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} ElementType;

typedef struct {
    ElementType type;
    union {
        int int_val;
        float float_val;
        char *str_val;
    } data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
} Tuple;

int tuple_init(Tuple *tuple, size_t size) {
    if (tuple == NULL || size == 0 || size > MAX_TUPLE_SIZE) {
        return 0;
    }
    
    tuple->elements = (TupleElement *)calloc(size, sizeof(TupleElement));
    if (tuple->elements == NULL) {
        return 0;
    }
    
    tuple->size = size;
    return 1;
}

void tuple_free(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type == TYPE_STRING && 
            tuple->elements[i].data.str_val != NULL) {
            free(tuple->elements[i].data.str_val);
        }
    }
    
    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0;
}

int tuple_set_int(Tuple *tuple, size_t index, int value) {
    if (tuple == NULL || tuple->elements == NULL || index >= tuple->size) {
        return 0;
    }
    
    tuple->elements[index].type = TYPE_INT;
    tuple->elements[index].data.int_val = value;
    return 1;
}

int tuple_set_float(Tuple *tuple, size_t index, float value) {
    if (tuple == NULL || tuple->elements == NULL || index >= tuple->size) {
        return 0;
    }
    
    tuple->elements[index].type = TYPE_FLOAT;
    tuple->elements[index].data.float_val = value;
    return 1;
}

int tuple_set_string(Tuple *tuple, size_t index, const char *value) {
    if (tuple == NULL || tuple->elements == NULL || index >= tuple->size || value == NULL) {
        return 0;
    }
    
    if (tuple->elements[index].type == TYPE_STRING && 
        tuple->elements[index].data.str_val != NULL) {
        free(tuple->elements[index].data.str_val);
    }
    
    tuple->elements[index].data.str_val = (char *)malloc(strlen(value) + 1);
    if (tuple->elements[index].data.str_val == NULL) {
        tuple->elements[index].type = TYPE_INT;
        tuple->elements[index].data.int_val = 0;
        return 0;
    }
    
    strcpy(tuple->elements[index].data.str_val, value);
    tuple->elements[index].type = TYPE_STRING;
    return 1;
}

int tuple_contains(Tuple *tuple, const TupleElement *element) {
    if (tuple == NULL || tuple->elements == NULL || element == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type != element->type) {
            continue;
        }
        
        switch (element->type) {
            case TYPE_INT:
                if (tuple->elements[i].data.int_val == element->data.int_val) {
                    return 1;
                }
                break;
                
            case TYPE_FLOAT:
                if (tuple->elements[i].data.float_val == element->data.float_val) {
                    return 1;
                }
                break;
                
            case TYPE_STRING:
                if (tuple->elements[i].data.str_val != NULL && 
                    element->data.str_val != NULL &&
                    strcmp(tuple->elements[i].data.str_val, element->data.str_val) == 0) {
                    return 1;
                }
                break;
                
            default:
                return 0;
        }
    }
    
    return 0;
}

int main(void) {
    Tuple tuple;
    TupleElement search_element;
    int found;
    
    if (!tuple_init(&tuple, 5)) {
        fprintf(stderr, "Failed to initialize tuple\n");
        return 1;
    }
    
    tuple_set_int(&tuple, 0, 42);
    tuple_set_float(&tuple, 1, 3.14f);
    tuple_set_string(&tuple, 2, "hello");
    tuple_set_int(&tuple, 3, 100);
    tuple_set_string(&tuple, 4, "world");
    
    search_element.type = TYPE_INT;
    search_element.data.int_val = 42;
    found = tuple_contains(&tuple, &search_element);
    printf("Contains int 42: %s\n", found ? "yes" : "no");
    
    search_element.type = TYPE_STRING;
    search_element.data.str_val = "hello";
    found = tuple_contains(&tuple, &search_element);
    printf("Contains string 'hello': %s\n", found ? "yes" : "no");
    
    search_element.type = TYPE_FLOAT;
    search_element.data.float_val = 2.71f;
    found = tuple_contains(&tuple, &search_element);
    printf("Contains float 2.71: %s\n", found ? "yes" : "no");
    
    tuple_free(&tuple);
    
    return 0;
}