#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int size;
    int *elements;
} Tuple;

typedef struct NestedTuple {
    int size;
    Tuple **tuples;
} NestedTuple;

NestedTuple* concatenate_tuples(const Tuple *tuple1, const Tuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return NULL;
    }

    NestedTuple *nested = (NestedTuple*)malloc(sizeof(NestedTuple));
    if (nested == NULL) {
        return NULL;
    }

    nested->size = 2;
    nested->tuples = (Tuple**)malloc(2 * sizeof(Tuple*));
    if (nested->tuples == NULL) {
        free(nested);
        return NULL;
    }

    nested->tuples[0] = (Tuple*)malloc(sizeof(Tuple));
    if (nested->tuples[0] == NULL) {
        free(nested->tuples);
        free(nested);
        return NULL;
    }

    nested->tuples[1] = (Tuple*)malloc(sizeof(Tuple));
    if (nested->tuples[1] == NULL) {
        free(nested->tuples[0]);
        free(nested->tuples);
        free(nested);
        return NULL;
    }

    nested->tuples[0]->size = tuple1->size;
    nested->tuples[0]->elements = (int*)malloc(tuple1->size * sizeof(int));
    if (nested->tuples[0]->elements == NULL && tuple1->size > 0) {
        free(nested->tuples[0]);
        free(nested->tuples[1]);
        free(nested->tuples);
        free(nested);
        return NULL;
    }

    for (int i = 0; i < tuple1->size; i++) {
        nested->tuples[0]->elements[i] = tuple1->elements[i];
    }

    nested->tuples[1]->size = tuple2->size;
    nested->tuples[1]->elements = (int*)malloc(tuple2->size * sizeof(int));
    if (nested->tuples[1]->elements == NULL && tuple2->size > 0) {
        free(nested->tuples[0]->elements);
        free(nested->tuples[0]);
        free(nested->tuples[1]);
        free(nested->tuples);
        free(nested);
        return NULL;
    }

    for (int i = 0; i < tuple2->size; i++) {
        nested->tuples[1]->elements[i] = tuple2->elements[i];
    }

    return nested;
}

void free_nested_tuple(NestedTuple *nested) {
    if (nested == NULL) {
        return;
    }

    if (nested->tuples != NULL) {
        for (int i = 0; i < nested->size; i++) {
            if (nested->tuples[i] != NULL) {
                free(nested->tuples[i]->elements);
                free(nested->tuples[i]);
            }
        }
        free(nested->tuples);
    }
    free(nested);
}

/* Possible weaknesses found:
 *  Parameter 'elements' can be declared as pointer to const [constParameterPointer]
 */
Tuple* create_tuple(int *elements, int size) {
    if (elements == NULL && size > 0) {
        return NULL;
    }

    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = size;
    tuple->elements = (int*)malloc(size * sizeof(int));
    if (tuple->elements == NULL && size > 0) {
        free(tuple);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        tuple->elements[i] = elements[i];
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    int elements1[] = {1, 2, 3};
    int elements2[] = {4, 5};

    Tuple *tuple1 = create_tuple(elements1, 3);
    Tuple *tuple2 = create_tuple(elements2, 2);

    if (tuple1 == NULL || tuple2 == NULL) {
        free_tuple(tuple1);
        free_tuple(tuple2);
        return 1;
    }

    NestedTuple *result = concatenate_tuples(tuple1, tuple2);
    if (result == NULL) {
        free_tuple(tuple1);
        free_tuple(tuple2);
        return 1;
    }

    printf("Nested tuple size: %d\n", result->size);
    for (int i = 0; i < result->size; i++) {
        printf("Tuple %d (size %d): ", i + 1, result->tuples[i]->size);
        for (int j = 0; j < result->tuples[i]->size; j++) {
            printf("%d ", result->tuples[i]->elements[j]);
        }
        printf("\n");
    }

    free_nested_tuple(result);
    free_tuple(tuple1);
    free_tuple(tuple2);

    return 0;
}