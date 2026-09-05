#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int tuple_compare(const Tuple *t1, const Tuple *t2) {
    size_t min_size;
    size_t i;
    
    if (t1 == NULL || t2 == NULL || t1->data == NULL || t2->data == NULL) {
        return 0;
    }
    
    min_size = t1->size < t2->size ? t1->size : t2->size;
    
    for (i = 0; i < min_size; i++) {
        if (t1->data[i] > t2->data[i]) {
            return 1;
        }
        if (t1->data[i] < t2->data[i]) {
            return -1;
        }
    }
    
    if (t1->size > t2->size) {
        return 1;
    }
    if (t1->size < t2->size) {
        return -1;
    }
    
    return 0;
}

Tuple* tuple_max(const Tuple *t1, const Tuple *t2) {
    Tuple *result;
    const Tuple *source;
    size_t i;
    
    if (t1 == NULL || t2 == NULL || t1->data == NULL || t2->data == NULL) {
        return NULL;
    }
    
    source = tuple_compare(t1, t2) >= 0 ? t1 : t2;
    
    result = malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }
    
    result->size = source->size;
    result->data = malloc(source->size * sizeof(int));
    if (result->data == NULL) {
        free(result);
        return NULL;
    }
    
    for (i = 0; i < source->size; i++) {
        result->data[i] = source->data[i];
    }
    
    return result;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        free(t);
    }
}

int main(void) {
    int data1[] = {3, 5, 7};
    int data2[] = {3, 5, 9};
    Tuple t1 = {data1, 3};
    Tuple t2 = {data2, 3};
    Tuple *max_tuple;
    size_t i;
    
    max_tuple = tuple_max(&t1, &t2);
    if (max_tuple == NULL) {
        fprintf(stderr, "Error: Failed to compute maximum tuple\n");
        return EXIT_FAILURE;
    }
    
    printf("Maximum tuple: (");
    for (i = 0; i < max_tuple->size; i++) {
        printf("%d", max_tuple->data[i]);
        if (i < max_tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
    
    tuple_free(max_tuple);
    
    return EXIT_SUCCESS;
}