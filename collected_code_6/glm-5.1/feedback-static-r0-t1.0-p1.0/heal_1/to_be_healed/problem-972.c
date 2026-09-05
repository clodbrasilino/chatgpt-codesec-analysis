#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple create_tuple(size_t size) {
    Tuple t;
    t.size = size;
    if (size > 0) {
        t.elements = (int *)malloc(size * sizeof(int));
        if (t.elements == NULL) {
            exit(EXIT_FAILURE);
        }
    } else {
        t.elements = NULL;
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

Tuple concatenate_to_nested(Tuple t1, Tuple t2) {
    Tuple nested;
    nested.size = 2;
    /* Possible weaknesses found:
     *  Result of 'malloc' is converted to a pointer of type 'int', which is incompatible with sizeof operand type 'Tuple *' [unix.MallocSizeof]
     *  Size of pointer 'elements' used instead of size of its data. [pointerSize]
     */
    nested.elements = (int *)malloc(nested.size * sizeof(Tuple *));
    if (nested.elements == NULL) {
        exit(EXIT_FAILURE);
    }

    Tuple *nested_items = (Tuple *)nested.elements;

    nested_items[0].size = t1.size;
    if (t1.size > 0) {
        nested_items[0].elements = (int *)malloc(t1.size * sizeof(int));
        if (nested_items[0].elements == NULL) {
            free(nested.elements);
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < t1.size; i++) {
            nested_items[0].elements[i] = t1.elements[i];
        }
    } else {
        nested_items[0].elements = NULL;
    }

    nested_items[1].size = t2.size;
    if (t2.size > 0) {
        nested_items[1].elements = (int *)malloc(t2.size * sizeof(int));
        if (nested_items[1].elements == NULL) {
            free(nested_items[0].elements);
            free(nested.elements);
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < t2.size; i++) {
            nested_items[1].elements[i] = t2.elements[i];
        }
    } else {
        nested_items[1].elements = NULL;
    }

    return nested;
}

void free_nested_tuple(Tuple *nested) {
    if (nested != NULL && nested->elements != NULL) {
        Tuple *nested_items = (Tuple *)nested->elements;
        free_tuple(&nested_items[0]);
        free_tuple(&nested_items[1]);
        free(nested->elements);
        nested->elements = NULL;
        nested->size = 0;
    }
}

int main(void) {
    Tuple t1 = create_tuple(2);
    t1.elements[0] = 1;
    t1.elements[1] = 2;

    Tuple t2 = create_tuple(3);
    t2.elements[0] = 3;
    t2.elements[1] = 4;
    t2.elements[2] = 5;

    Tuple nested = concatenate_to_nested(t1, t2);

    Tuple *items = (Tuple *)nested.elements;

    printf("Nested Tuple:\n");
    printf("Tuple 1: ");
    for (size_t i = 0; i < items[0].size; i++) {
        printf("%d ", items[0].elements[i]);
    }
    printf("\n");

    printf("Tuple 2: ");
    for (size_t i = 0; i < items[1].size; i++) {
        printf("%d ", items[1].elements[i]);
    }
    printf("\n");

    free_tuple(&t1);
    free_tuple(&t2);
    free_nested_tuple(&nested);

    return 0;
}