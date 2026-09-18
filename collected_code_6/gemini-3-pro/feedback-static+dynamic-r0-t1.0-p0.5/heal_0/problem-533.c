#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        char *s;
    } data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->elements = (TupleElement*)calloc(size, sizeof(TupleElement));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    for (size_t i = 0; i < tuple->size; ++i) {
        if (tuple->elements[i].type == TYPE_STRING && tuple->elements[i].data.s) {
            free(tuple->elements[i].data.s);
        }
    }
    free(tuple->elements);
    free(tuple);
}

Tuple* remove_elements_by_type(const Tuple *input_tuple, DataType type_to_remove) {
    if (!input_tuple || !input_tuple->elements) {
        return NULL;
    }

    size_t new_size = 0;
    for (size_t i = 0; i < input_tuple->size; ++i) {
        if (input_tuple->elements[i].type != type_to_remove) {
            new_size++;
        }
    }

    Tuple *new_tuple = create_tuple(new_size);
    if (!new_tuple) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < input_tuple->size; ++i) {
        if (input_tuple->elements[i].type != type_to_remove) {
            new_tuple->elements[j].type = input_tuple->elements[i].type;
            if (input_tuple->elements[i].type == TYPE_STRING) {
                if (input_tuple->elements[i].data.s) {
                    new_tuple->elements[j].data.s = strdup(input_tuple->elements[i].data.s);
                    if (!new_tuple->elements[j].data.s) {
                        free_tuple(new_tuple);
                        return NULL;
                    }
                } else {
                    new_tuple->elements[j].data.s = NULL;
                }
            } else {
                new_tuple->elements[j].data = input_tuple->elements[i].data;
            }
            j++;
        }
    }

    return new_tuple;
}

void print_tuple(const Tuple *tuple) {
    if (!tuple) {
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
            case TYPE_STRING:
                printf("\"%s\"", tuple->elements[i].data.s ? tuple->elements[i].data.s : "NULL");
                break;
        }
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple *tuple = create_tuple(5);
    if (!tuple) {
        return 1;
    }

    tuple->elements[0].type = TYPE_INT;
    tuple->elements[0].data.i = 10;

    tuple->elements[1].type = TYPE_STRING;
    tuple->elements[1].data.s = strdup("Hello");
    if (!tuple->elements[1].data.s) {
        free_tuple(tuple);
        return 1;
    }

    tuple->elements[2].type = TYPE_FLOAT;
    tuple->elements[2].data.f = 3.14f;

    tuple->elements[3].type = TYPE_STRING;
    tuple->elements[3].data.s = strdup("World");
    if (!tuple->elements[3].data.s) {
        free_tuple(tuple);
        return 1;
    }

    tuple->elements[4].type = TYPE_INT;
    tuple->elements[4].data.i = 42;

    Tuple *filtered_tuple = remove_elements_by_type(tuple, TYPE_STRING);
    if (!filtered_tuple) {
        free_tuple(tuple);
        return 1;
    }

    print_tuple(filtered_tuple);

    free_tuple(tuple);
    free_tuple(filtered_tuple);

    return 0;
}