#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int type; // 0 for int, 1 for float, 2 for nested tuple
    union {
        int i;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::f' is never used. [unusedStructMember]
         */
        float f;
        /* Possible weaknesses found:
         *  forward declaration of 'struct Tuple'
         */
        struct Tuple *t;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

bool is_even(int num) {
    return num % 2 == 0;
}

/* Possible weaknesses found:
 *  expected 'Tuple *' but argument is of type 'struct Tuple *'
 */
Tuple* extract_even_elements(Tuple *tuple) {
    if (!tuple || !tuple->elements) return NULL;

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    result->count = 0;
    result->elements = (TupleElement *)malloc(tuple->count * sizeof(TupleElement));

    for (size_t i = 0; i < tuple->count; ++i) {
        if (tuple->elements[i].type == 0 && is_even(tuple->elements[i].value.i)) {
            result->elements[result->count++] = tuple->elements[i];
        } else if (tuple->elements[i].type == 2) {
            /* Possible weaknesses found:
             *  passing argument 1 of 'extract_even_elements' from incompatible pointer type [-Wincompatible-pointer-types]
             */
            Tuple *nested_result = extract_even_elements(tuple->elements[i].value.t);
            for (size_t j = 0; j < nested_result->count; ++j) {
                result->elements[result->count++] = nested_result->elements[j];
            }
            free(nested_result->elements);
            free(nested_result);
        }
    }

    result->elements = (TupleElement *)realloc(result->elements, result->count * sizeof(TupleElement));
    return result;
}

/* Possible weaknesses found:
 *  expected 'Tuple *' but argument is of type 'struct Tuple *'
 */
void free_tuple(Tuple *tuple) {
    if (tuple) {
        if (tuple->elements) {
            for (size_t i = 0; i < tuple->count; ++i) {
                if (tuple->elements[i].type == 2) {
                    /* Possible weaknesses found:
                     *  passing argument 1 of 'free_tuple' from incompatible pointer type [-Wincompatible-pointer-types]
                     */
                    free_tuple(tuple->elements[i].value.t);
                }
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main() {
    Tuple *input_tuple = (Tuple *)malloc(sizeof(Tuple));
    input_tuple->count = 3;
    input_tuple->elements = (TupleElement *)malloc(input_tuple->count * sizeof(TupleElement));

    input_tuple->elements[0].type = 0;
    input_tuple->elements[0].value.i = 1;

    input_tuple->elements[1].type = 2;
    /* Possible weaknesses found:
     *  assignment to 'struct Tuple *' from incompatible pointer type 'Tuple *' [-Wincompatible-pointer-types]
     */
    input_tuple->elements[1].value.t = (Tuple *)malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  invalid use of undefined type 'struct Tuple'
     *  incomplete definition of type 'struct Tuple'
     */
    input_tuple->elements[1].value.t->count = 2;
    /* Possible weaknesses found:
     *  invalid use of undefined type 'struct Tuple'
     *  incomplete definition of type 'struct Tuple'
     */
    input_tuple->elements[1].value.t->elements = (TupleElement *)malloc(2 * sizeof(TupleElement));
    /* Possible weaknesses found:
     *  invalid use of undefined type 'struct Tuple'
     *  incomplete definition of type 'struct Tuple'
     */
    input_tuple->elements[1].value.t->elements[0].type = 0;
    /* Possible weaknesses found:
     *  invalid use of undefined type 'struct Tuple'
     *  incomplete definition of type 'struct Tuple'
     */
    input_tuple->elements[1].value.t->elements[0].value.i = 2;
    /* Possible weaknesses found:
     *  invalid use of undefined type 'struct Tuple'
     *  incomplete definition of type 'struct Tuple'
     */
    input_tuple->elements[1].value.t->elements[1].type = 0;
    /* Possible weaknesses found:
     *  invalid use of undefined type 'struct Tuple'
     *  incomplete definition of type 'struct Tuple'
     */
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