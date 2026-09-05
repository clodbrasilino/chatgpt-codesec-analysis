#include <stdlib.h>
#include <stdio.h>

int *pairwise_add(const int *a, const int *b, size_t size) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    if (size == 0) {
        return NULL;
    }
    int *result = malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
    return result;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'tuple2' can be declared as const array [constVariable]
     */
    int tuple2[] = {6, 7, 8, 9, 10};
    size_t size = sizeof(tuple1) / sizeof(tuple1[0]);
    
    int *result = pairwise_add(tuple1, tuple2, size);
    if (result == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    result = NULL;
    
    return EXIT_SUCCESS;
}