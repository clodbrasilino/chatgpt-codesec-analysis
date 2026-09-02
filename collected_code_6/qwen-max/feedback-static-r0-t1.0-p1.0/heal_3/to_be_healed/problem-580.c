#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tuple Tuple;

typedef struct {
    int type; 
    union {
        int i;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::f' is never used. [unusedStructMember]
         */
        float f;
        Tuple *t;
    } value;
} TupleElement;

struct Tuple {
    TupleElement *elements;
    size_t count;
};

bool is_even(int num) {
    return num % 2 == 0;
}

Tuple* extract_even_elements(Tuple *tuple) {
    if (!tuple || !tuple->elements) return NULL;

    Tuple *result = malloc(sizeof(Tuple));
    result->count = 0;
    result->elements = malloc(tuple->count * sizeof(TupleElement));

    for (size_t i = 0; i < tuple->count; ++i) {
        if (tuple->elements[i].type == 0 && is_even(tuple->elements[i].value.i)) {
            result->elements[result->count++] = tuple->elements[i];
        } else if (tuple->elements[i].type == 2) {
            Tuple *nested_result = extract_even_elements(tuple->elements[i].value.t);
            for (size_t j = 0; j < nested_result->count; ++j) {
                result->elements[result->count++] = nested_result->elements[j];
            }
            free(nested_result->elements);
            free(nested_result);
        }
    }

    result->elements = realloc(result->elements, result->count * sizeof(TupleElement));
    return result;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        if (tuple->elements) {
            for (size_t i = 0; i < tuple->count; ++i) {
                if (tuple->elements[i].type == 2) {
                    free_tuple(tuple->elements[i].value.t);
                }
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main() {
    Tuple *input_tuple = malloc(sizeof(Tuple));
    input_tuple->count = 3;
    input_tuple->elements = malloc(input_tuple->count * sizeof(TupleElement));

    input_tuple->elements[0].type = 0;
    input_tuple->elements[0].value.i = 1;

    input_tuple->elements[1].type = 2;
    input_tuple->elements[1].value.t = malloc(sizeof(Tuple));
    input_tuple->elements[1].value.t->count = 2;
    input_tuple->elements[1].value.t->elements = malloc(2 * sizeof(TupleElement));
    input_tuple->elements[1].value.t->elements[0].type = 0;
    input_tuple->elements[1].value.t->elements[0].value.i = 2;
    input_tuple->elements[1].value.t->elements[1].type = 0;
    input_tuple->elements[1].value.t->elements[1].value.i = 3;

    input_tuple->elements[2].type = 0;
    input_tuple->elements[2].value.i = 4;

    Tuple *even_elements = extract_even_elements(input_tuple);

    for (size_t i = 0; i < even_elements->count; ++i) {
        if (even_elements->elements[i].type == 0) {
            printf("%d ", even_elements->elements[i].value.i);
        }
    }
    printf("\n");

    free_tuple(input_tuple);
    free_tuple(even_elements);

    return 0;
}