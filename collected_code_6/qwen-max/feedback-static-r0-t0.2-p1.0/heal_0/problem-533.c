#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; // 0 for int, 1 for float, 2 for char
    union {
        int i;
        float f;
        char c;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

Tuple* create_tuple(size_t count) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    tuple->elements = (TupleElement*)malloc(count * sizeof(TupleElement));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    tuple->count = count;
    return tuple;
}

void destroy_tuple(Tuple *tuple) {
    if (tuple) {
        free(tuple->elements);
        free(tuple);
    }
}

Tuple* remove_elements_by_type(Tuple *tuple, int type) {
    if (!tuple) return NULL;
    Tuple *new_tuple = create_tuple(tuple->count);
    if (!new_tuple) return NULL;
    
    size_t new_count = 0;
    for (size_t i = 0; i < tuple->count; ++i) {
        if (tuple->elements[i].type != type) {
            if (new_count >= new_tuple->count) {
                TupleElement *temp = (TupleElement*)realloc(new_tuple->elements, (new_count + 1) * sizeof(TupleElement));
                if (!temp) {
                    destroy_tuple(new_tuple);
                    return NULL;
                }
                new_tuple->elements = temp;
                new_tuple->count = new_count + 1;
            }
            new_tuple->elements[new_count] = tuple->elements[i];
            new_count++;
        }
    }
    new_tuple->count = new_count;
    return new_tuple;
}

int main() {
    Tuple *tuple = create_tuple(5);
    if (!tuple) return 1;

    tuple->elements[0].type = 0; tuple->elements[0].value.i = 10;
    tuple->elements[1].type = 1; tuple->elements[1].value.f = 20.5f;
    tuple->elements[2].type = 2; tuple->elements[2].value.c = 'A';
    tuple->elements[3].type = 0; tuple->elements[3].value.i = 30;
    tuple->elements[4].type = 1; tuple->elements[4].value.f = 40.75f;

    Tuple *filtered_tuple = remove_elements_by_type(tuple, 1);
    if (!filtered_tuple) {
        destroy_tuple(tuple);
        return 1;
    }

    for (size_t i = 0; i < filtered_tuple->count; ++i) {
        switch (filtered_tuple->elements[i].type) {
            case 0: printf("%d ", filtered_tuple->elements[i].value.i); break;
            case 1: printf("%f ", filtered_tuple->elements[i].value.f); break;
            case 2: printf("%c ", filtered_tuple->elements[i].value.c); break;
        }
    }
    printf("\n");

    destroy_tuple(tuple);
    destroy_tuple(filtered_tuple);
    return 0;
}