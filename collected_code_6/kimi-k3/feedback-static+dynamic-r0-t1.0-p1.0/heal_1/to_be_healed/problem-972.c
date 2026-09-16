#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} NestedTuple;

Tuple create_tuple(const int *arr, size_t size) {
    Tuple t;
    t.size = size;
    t.data = NULL;
    
    if (size > 0) {
        t.data = (int *)malloc(size * sizeof(int));
        if (t.data != NULL) {
            for (size_t i = 0; i < size; i++) {
                t.data[i] = arr[i];
            }
        } else {
            t.size = 0;
        }
    }
    
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

NestedTuple concatenate_to_nested(const Tuple *t1, const Tuple *t2) {
    NestedTuple nested;
    nested.size = 0;
    nested.tuples = NULL;
    
    if (t1 == NULL || t2 == NULL) {
        return nested;
    }
    
    nested.tuples = (Tuple *)malloc(2 * sizeof(Tuple));
    if (nested.tuples == NULL) {
        return nested;
    }
    
    nested.tuples[0].size = t1->size;
    nested.tuples[0].data = NULL;
    if (t1->size > 0) {
        nested.tuples[0].data = (int *)malloc(t1->size * sizeof(int));
        if (nested.tuples[0].data == NULL) {
            free(nested.tuples);
            nested.tuples = NULL;
            return nested;
        }
        for (size_t i = 0; i < t1->size; i++) {
            nested.tuples[0].data[i] = t1->data[i];
        }
    }
    
    nested.tuples[1].size = t2->size;
    nested.tuples[1].data = NULL;
    if (t2->size > 0) {
        nested.tuples[1].data = (int *)malloc(t2->size * sizeof(int));
        if (nested.tuples[1].data == NULL) {
            free(nested.tuples[0].data);
            free(nested.tuples);
            nested.tuples = NULL;
            return nested;
        }
        for (size_t i = 0; i < t2->size; i++) {
            nested.tuples[1].data[i] = t2->data[i];
        }
    }
    
    nested.size = 2;
    return nested;
}

void free_nested_tuple(NestedTuple *nested) {
    if (nested != NULL && nested->tuples != NULL) {
        for (size_t i = 0; i < nested->size; i++) {
            free(nested->tuples[i].data);
        }
        free(nested->tuples);
        nested->tuples = NULL;
        nested->size = 0;
    }
}

void print_tuple(const Tuple *t) {
    if (t == NULL) {
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        printf("%d", t->data[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")");
}

void print_nested_tuple(const NestedTuple *nested) {
    if (nested == NULL) {
        return;
    }
    printf("(");
    for (size_t i = 0; i < nested->size; i++) {
        print_tuple(&nested->tuples[i]);
        if (i < nested->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {4, 5, 6};
    
    Tuple t1 = create_tuple(arr1, 3);
    Tuple t2 = create_tuple(arr2, 3);
    
    if (t1.data == NULL || t2.data == NULL) {
        free_tuple(&t1);
        free_tuple(&t2);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    NestedTuple nested = concatenate_to_nested(&t1, &t2);
    
    if (nested.tuples == NULL) {
        free_tuple(&t1);
        free_tuple(&t2);
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Nested tuple: ");
    print_nested_tuple(&nested);
    
    free_tuple(&t1);
    free_tuple(&t2);
    free_nested_tuple(&nested);
    
    return EXIT_SUCCESS;
}