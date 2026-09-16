#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} NestedTuple;

NestedTuple* concatenateToNestedTuple(const Tuple* tuple1, const Tuple* tuple2) {
    if (!tuple1 || !tuple2) {
        return NULL;
    }

    NestedTuple* nestedTuple = (NestedTuple*)malloc(sizeof(NestedTuple));
    if (!nestedTuple) {
        return NULL;
    }

    nestedTuple->size = 2;
    nestedTuple->tuples = (Tuple*)malloc(nestedTuple->size * sizeof(Tuple));
    if (!nestedTuple->tuples) {
        free(nestedTuple);
        return NULL;
    }

    nestedTuple->tuples[0].size = tuple1->size;
    nestedTuple->tuples[0].elements = (int*)malloc(tuple1->size * sizeof(int));
    if (!nestedTuple->tuples[0].elements) {
        free(nestedTuple->tuples);
        free(nestedTuple);
        return NULL;
    }
    for (size_t i = 0; i < tuple1->size; ++i) {
        nestedTuple->tuples[0].elements[i] = tuple1->elements[i];
    }

    nestedTuple->tuples[1].size = tuple2->size;
    nestedTuple->tuples[1].elements = (int*)malloc(tuple2->size * sizeof(int));
    if (!nestedTuple->tuples[1].elements) {
        free(nestedTuple->tuples[0].elements);
        free(nestedTuple->tuples);
        free(nestedTuple);
        return NULL;
    }
    for (size_t i = 0; i < tuple2->size; ++i) {
        nestedTuple->tuples[1].elements[i] = tuple2->elements[i];
    }

    return nestedTuple;
}

void freeNestedTuple(NestedTuple* nestedTuple) {
    if (!nestedTuple) {
        return;
    }
    if (nestedTuple->tuples) {
        for (size_t i = 0; i < nestedTuple->size; ++i) {
            free(nestedTuple->tuples[i].elements);
        }
        free(nestedTuple->tuples);
    }
    free(nestedTuple);
}

int main(void) {
    int elems1[] = {1, 2, 3};
    int elems2[] = {4, 5};

    Tuple tuple1 = {elems1, sizeof(elems1) / sizeof(elems1[0])};
    Tuple tuple2 = {elems2, sizeof(elems2) / sizeof(elems2[0])};

    NestedTuple* nested = concatenateToNestedTuple(&tuple1, &tuple2);
    if (!nested) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < nested->size; ++i) {
        printf("Tuple %zu: (", i + 1);
        for (size_t j = 0; j < nested->tuples[i].size; ++j) {
            printf("%d", nested->tuples[i].elements[j]);
            if (j < nested->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    freeNestedTuple(nested);

    return EXIT_SUCCESS;
}