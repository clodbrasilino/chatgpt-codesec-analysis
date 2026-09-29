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

NestedTuple* concatenate_tuples_to_nested(const Tuple *t1, const Tuple *t2) {
    if (!t1 || !t2) {
        return NULL;
    }

    NestedTuple *nested = (NestedTuple *)malloc(sizeof(NestedTuple));
    if (!nested) {
        return NULL;
    }

    nested->size = 2;
    nested->tuples = (Tuple *)malloc(nested->size * sizeof(Tuple));
    if (!nested->tuples) {
        free(nested);
        return NULL;
    }

    nested->tuples[0].size = t1->size;
    nested->tuples[0].elements = (int *)malloc(t1->size * sizeof(int));
    if (!nested->tuples[0].elements) {
        free(nested->tuples);
        free(nested);
        return NULL;
    }
    for (size_t i = 0; i < t1->size; i++) {
        nested->tuples[0].elements[i] = t1->elements[i];
    }

    nested->tuples[1].size = t2->size;
    nested->tuples[1].elements = (int *)malloc(t2->size * sizeof(int));
    if (!nested->tuples[1].elements) {
        free(nested->tuples[0].elements);
        free(nested->tuples);
        free(nested);
        return NULL;
    }
    for (size_t i = 0; i < t2->size; i++) {
        nested->tuples[1].elements[i] = t2->elements[i];
    }

    return nested;
}

void free_nested_tuple(NestedTuple *nested) {
    if (nested) {
        if (nested->tuples) {
            for (size_t i = 0; i < nested->size; i++) {
                free(nested->tuples[i].elements);
            }
            free(nested->tuples);
        }
        free(nested);
    }
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};

    Tuple t1 = {arr1, 3};
    Tuple t2 = {arr2, 2};

    NestedTuple *nested = concatenate_tuples_to_nested(&t1, &t2);
    if (!nested) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < nested->size; i++) {
        printf("Tuple %zu: (", i);
        for (size_t j = 0; j < nested->tuples[i].size; j++) {
            printf("%d", nested->tuples[i].elements[j]);
            if (j < nested->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_nested_tuple(nested);

    return EXIT_SUCCESS;
}