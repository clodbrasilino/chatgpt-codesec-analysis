#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

Tuple create_tuple(const int *values, size_t size) {
    Tuple t;
    t.size = size;
    t.data = (int *)malloc(size * sizeof(int));
    if (t.data == NULL) {
        t.size = 0;
        return t;
    }
    for (size_t i = 0; i < size; i++) {
        t.data[i] = values[i];
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL && t->data != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int *extract_elementwise(const Tuple *t1, const Tuple *t2, size_t *out_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'out_size==NULL' is not redundant
     */
    if (t1 == NULL || t2 == NULL || out_size == NULL || t1->data == NULL || t2->data == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'out_size==NULL' is redundant or there is possible null pointer dereference: out_size. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *out_size = 0;
        return NULL;
    }
    
    size_t min_size = t1->size < t2->size ? t1->size : t2->size;
    if (min_size == 0) {
        *out_size = 0;
        return NULL;
    }
    
    int *result = (int *)malloc(min_size * sizeof(int));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }
    
    for (size_t i = 0; i < min_size; i++) {
        result[i] = t1->data[i] + t2->data[i];
    }
    
    *out_size = min_size;
    return result;
}

TupleList extract_tuples(const Tuple *t1, const Tuple *t2) {
    TupleList result;
    result.tuples = NULL;
    result.count = 0;
    
    if (t1 == NULL || t2 == NULL || t1->data == NULL || t2->data == NULL) {
        return result;
    }
    
    size_t min_size = t1->size < t2->size ? t1->size : t2->size;
    if (min_size == 0) {
        return result;
    }
    
    result.tuples = (Tuple *)malloc(min_size * sizeof(Tuple));
    if (result.tuples == NULL) {
        return result;
    }
    
    result.count = min_size;
    
    for (size_t i = 0; i < min_size; i++) {
        int pair[2];
        pair[0] = t1->data[i];
        pair[1] = t2->data[i];
        result.tuples[i] = create_tuple(pair, 2);
        if (result.tuples[i].data == NULL) {
            for (size_t j = 0; j < i; j++) {
                free_tuple(&result.tuples[j]);
            }
            free(result.tuples);
            result.tuples = NULL;
            result.count = 0;
            return result;
        }
    }
    
    return result;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->tuples != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free_tuple(&list->tuples[i]);
        }
        free(list->tuples);
        list->tuples = NULL;
    }
    list->count = 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {10, 20, 30, 40, 50};
    
    Tuple t1 = create_tuple(arr1, 5);
    Tuple t2 = create_tuple(arr2, 5);
    
    if (t1.data == NULL || t2.data == NULL) {
        free_tuple(&t1);
        free_tuple(&t2);
        return 1;
    }
    
    size_t elem_size = 0;
    int *elementwise = extract_elementwise(&t1, &t2, &elem_size);
    
    if (elementwise != NULL) {
        printf("Elementwise sum: ");
        for (size_t i = 0; i < elem_size; i++) {
            printf("%d ", elementwise[i]);
        }
        printf("\n");
        free(elementwise);
    }
    
    TupleList tuples = extract_tuples(&t1, &t2);
    
    if (tuples.tuples != NULL) {
        printf("Extracted tuples:\n");
        for (size_t i = 0; i < tuples.count; i++) {
            if (tuples.tuples[i].data != NULL && tuples.tuples[i].size == 2) {
                printf("  (%d, %d)\n", tuples.tuples[i].data[0], tuples.tuples[i].data[1]);
            }
        }
        free_tuple_list(&tuples);
    }
    
    free_tuple(&t1);
    free_tuple(&t2);
    
    return 0;
}