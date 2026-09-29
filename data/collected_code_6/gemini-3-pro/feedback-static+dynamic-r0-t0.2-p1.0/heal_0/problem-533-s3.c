#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        char c;
    } data;
} Element;

typedef struct {
    Element* elements;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->elements = (Element*)malloc(size * sizeof(Element));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple) {
        free(tuple->elements);
        free(tuple);
    }
}

Tuple* remove_elements_by_type(const Tuple* input, DataType type_to_remove) {
    if (!input || !input->elements) {
        return NULL;
    }

    size_t new_size = 0;
    for (size_t i = 0; i < input->size; ++i) {
        if (input->elements[i].type != type_to_remove) {
            new_size++;
        }
    }

    Tuple* result = create_tuple(new_size);
    if (!result) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < input->size; ++i) {
        if (input->elements[i].type != type_to_remove) {
            result->elements[index++] = input->elements[i];
        }
    }

    return result;
}

void print_tuple(const Tuple* tuple) {
    if (!tuple || !tuple->elements) {
        return;
    }
    printf("(");
    for (size_t i = 0; i < tuple->size; ++i) {
        switch (tuple->elements[i].type) {
            case TYPE_INT:
                printf("%d", tuple->elements[i].data.i);
                break;
            case TYPE_FLOAT:
                printf("%f", tuple->elements[i].data.f);
                break;
            case TYPE_CHAR:
                printf("'%c'", tuple->elements[i].data.c);
                break;
        }
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple* tuple = create_tuple(5);
    if (!tuple) {
        return 1;
    }

    tuple->elements[0].type = TYPE_INT;
    tuple->elements[0].data.i = 10;
    
    tuple->elements[1].type = TYPE_FLOAT;
    tuple->elements[1].data.f = 3.14f;
    
    tuple->elements[2].type = TYPE_CHAR;
    tuple->elements[2].data.c = 'A';
    
    tuple->elements[3].type = TYPE_INT;
    tuple->elements[3].data.i = 20;
    
    tuple->elements[4].type = TYPE_FLOAT;
    tuple->elements[4].data.f = 2.71f;

    Tuple* filtered_tuple = remove_elements_by_type(tuple, TYPE_INT);
    if (!filtered_tuple) {
        free_tuple(tuple);
        return 1;
    }

    print_tuple(filtered_tuple);

    free_tuple(tuple);
    free_tuple(filtered_tuple);

    return 0;
}