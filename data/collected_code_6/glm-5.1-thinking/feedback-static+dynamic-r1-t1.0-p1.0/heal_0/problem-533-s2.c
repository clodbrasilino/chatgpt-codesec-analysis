#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR
} DataType;

typedef union {
    int int_val;
    float float_val;
    char char_val;
} Value;

typedef struct {
    DataType type;
    Value value;
} Element;

typedef struct {
    Element *elements;
    int size;
} Tuple;

Tuple remove_elements_by_type(const Tuple *tuple, DataType target) {
    Tuple result = {NULL, 0};

    if (tuple == NULL || tuple->size < 0) {
        return result;
    }

    int new_size = 0;
    for (int i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type != target) {
            new_size++;
        }
    }

    if (new_size == 0) {
        return result;
    }

    result.elements = (Element *)malloc(sizeof(Element) * new_size);
    if (result.elements == NULL) {
        return result;
    }

    result.size = new_size;
    int index = 0;
    for (int i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type != target) {
            result.elements[index] = tuple->elements[i];
            index++;
        }
    }

    return result;
}

int main(void) {
    Element items[5];
    
    items[0].type = TYPE_INT;
    items[0].value.int_val = 10;
    
    items[1].type = TYPE_FLOAT;
    items[1].value.float_val = 3.14f;
    
    items[2].type = TYPE_CHAR;
    items[2].value.char_val = 'x';
    
    items[3].type = TYPE_INT;
    items[3].value.int_val = 20;
    
    items[4].type = TYPE_CHAR;
    items[4].value.char_val = 'y';

    Tuple original = {items, 5};

    Tuple filtered = remove_elements_by_type(&original, TYPE_INT);

    for (int i = 0; i < filtered.size; i++) {
        switch (filtered.elements[i].type) {
            case TYPE_INT:
                printf("INT: %d\n", filtered.elements[i].value.int_val);
                break;
            case TYPE_FLOAT:
                printf("FLOAT: %f\n", filtered.elements[i].value.float_val);
                break;
            case TYPE_CHAR:
                printf("CHAR: %c\n", filtered.elements[i].value.char_val);
                break;
        }
    }

    free(filtered.elements);

    return 0;
}