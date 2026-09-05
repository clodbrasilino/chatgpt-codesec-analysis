#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
} Record;

typedef struct {
    int type;
    union {
        int int_val;
        Record *rec;
    } data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

Tuple *remove_nested_record(Tuple *tuple, size_t index) {
    Tuple *new_tuple;
    size_t new_count;
    size_t i, j;

    if (tuple == NULL || index >= tuple->count) {
        return NULL;
    }

    new_count = tuple->count - 1;
    new_tuple = (Tuple *)malloc(sizeof(Tuple));
    if (new_tuple == NULL) {
        return NULL;
    }

    new_tuple->elements = (TupleElement *)malloc(new_count * sizeof(TupleElement));
    if (new_tuple->elements == NULL) {
        free(new_tuple);
        return NULL;
    }

    new_tuple->count = new_count;

    for (i = 0, j = 0; i < tuple->count; i++) {
        if (i != index) {
            new_tuple->elements[j] = tuple->elements[i];
            j++;
        }
    }

    return new_tuple;
}

void free_tuple(Tuple *tuple) {
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (tuple == NULL) {
        return;
    }

    if (tuple->elements != NULL) {
        for (i = 0; i < tuple->count; i++) {
            if (tuple->elements[i].type == 1 && tuple->elements[i].data.rec != NULL) {
                free(tuple->elements[i].data.rec);
            }
        }
        free(tuple->elements);
    }
    free(tuple);
}

int main(void) {
    Tuple *original;
    Tuple *result;
    size_t i;

    original = (Tuple *)malloc(sizeof(Tuple));
    if (original == NULL) {
        return EXIT_FAILURE;
    }

    original->count = 3;
    original->elements = (TupleElement *)malloc(3 * sizeof(TupleElement));
    if (original->elements == NULL) {
        free(original);
        return EXIT_FAILURE;
    }

    original->elements[0].type = 0;
    original->elements[0].data.int_val = 42;

    original->elements[1].type = 1;
    original->elements[1].data.rec = (Record *)malloc(sizeof(Record));
    if (original->elements[1].data.rec == NULL) {
        free(original->elements);
        free(original);
        return EXIT_FAILURE;
    }
    original->elements[1].data.rec->id = 100;
    original->elements[1].data.rec->value = 3.14f;

    original->elements[2].type = 0;
    original->elements[2].data.int_val = 99;

    result = remove_nested_record(original, 1);
    if (result == NULL) {
        free_tuple(original);
        return EXIT_FAILURE;
    }

    printf("Result tuple count: %zu\n", result->count);
    for (i = 0; i < result->count; i++) {
        if (result->elements[i].type == 0) {
            printf("Element %zu: int = %d\n", i, result->elements[i].data.int_val);
        }
    }

    free_tuple(original);
    free_tuple(result);

    return EXIT_SUCCESS;
}