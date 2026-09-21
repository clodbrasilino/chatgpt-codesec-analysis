#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int compare_tuples(const Tuple *t1, const Tuple *t2) {
    size_t min_size = (t1->size < t2->size) ? t1->size : t2->size;
    
    for (size_t i = 0; i < min_size; i++) {
        if (t1->data[i] < t2->data[i]) {
            return -1;
        }
        if (t1->data[i] > t2->data[i]) {
            return 1;
        }
    }
    
    if (t1->size < t2->size) {
        return -1;
    }
    if (t1->size > t2->size) {
        return 1;
    }
    
    return 0;
}

Tuple maximize_tuples(const Tuple *t1, const Tuple *t2) {
    Tuple result = {NULL, 0};
    const Tuple *source;
    
    if (t1 == NULL || t2 == NULL || t1->data == NULL || t2->data == NULL) {
        return result;
    }
    
    source = (compare_tuples(t1, t2) >= 0) ? t1 : t2;
    
    if (source->size == 0) {
        return result;
    }
    
    if (source->size > SIZE_MAX / sizeof(int)) {
        return result;
    }
    
    result.data = malloc(source->size * sizeof(int));
    if (result.data == NULL) {
        return result;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result.data, source->data, source->size * sizeof(int));
    result.size = source->size;
    
    return result;
}

void free_tuple(Tuple *t) {
    if (t != NULL && t->data != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int main(void) {
    int arr1[] = {1, 5, 3};
    int arr2[] = {2, 4, 6};
    
    Tuple t1 = {arr1, 3};
    Tuple t2 = {arr2, 3};
    
    Tuple max_tuple = maximize_tuples(&t1, &t2);
    
    if (max_tuple.data != NULL) {
        printf("Max tuple: ");
        for (size_t i = 0; i < max_tuple.size; i++) {
            printf("%d ", max_tuple.data[i]);
        }
        printf("\n");
        free_tuple(&max_tuple);
    } else {
        fprintf(stderr, "Error: Failed to compute max tuple\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}