#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INT,
    FLOAT,
    STRING
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
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    tuple->elements = (TupleElement *)malloc(size * sizeof(TupleElement));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        if (tuple->elements) {
            for (size_t i = 0; i < tuple->size; i++) {
                if (tuple->elements[i].type == STRING && tuple->elements[i].data.s != NULL) {
                    free(tuple->elements[i].data.s);
                }
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

Tuple* remove_elements_by_type(Tuple *tuple, DataType type_to_remove) {
    if (!tuple || !tuple->elements) return NULL;

    size_t new_size = 0;
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type != type_to_remove) {
            new_size++;
        }
    }

    Tuple *new_tuple = create_tuple(new_size);
    if (!new_tuple) return NULL;

    size_t new_index = 0;
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].type != type_to_remove) {
            new_tuple->elements[new_index].type = tuple->elements[i].type;
            if (tuple->elements[i].type == STRING) {
                if (tuple->elements[i].data.s) {
                    new_tuple->elements[new_index].data.s = strdup(tuple->elements[i].data.s);
                    if (!new_tuple->elements[new_index].data.s) {
                        free_tuple(new_tuple);
                        return NULL;
                    }
                } else {
                    new_tuple->elements[new_index].data.s = NULL;
                }
            } else {
                new_tuple->elements[new_index].data = tuple->elements[i].data;
            }
            new_index++;
        }
    }

    return new_tuple;
}

void print_tuple(Tuple *tuple) {
    if (!tuple || !tuple->elements) return;
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        switch (tuple->elements[i].type) {
            case INT:
                printf("%d", tuple->elements[i].data.i);
                break;
            case FLOAT:
                printf("%f", tuple->elements[i].data.f);
                break;
            case STRING:
                printf("\"%s\"", tuple->elements[i].data.s ? tuple->elements[i].data.s : "");
                break;
        }
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main() {
    Tuple *tuple = create_tuple(5);
    if (!tuple) return 1;

    tuple->elements[0].type = INT;
    tuple->elements[0].data.i = 10;

    tuple->elements[1].type = FLOAT;
    tuple->elements[1].data.f = 3.14f;

    tuple->elements[2].type = STRING;
    tuple->elements[2].data.s = strdup("hello");

    tuple->elements[3].type = INT;
    tuple->elements[3].data.i = 20;

    tuple->elements[4].type = FLOAT;
    tuple->elements[4].data.f = 2.71f;

    if (!tuple->elements[2].data.s) {
        free_tuple(tuple);
        return 1;
    }

    Tuple *filtered_tuple = remove_elements_by_type(tuple, INT);
    if (filtered_tuple) {
        print_tuple(filtered_tuple);
        free_tuple(filtered_tuple);
    }

    free_tuple(tuple);
    return 0;
}