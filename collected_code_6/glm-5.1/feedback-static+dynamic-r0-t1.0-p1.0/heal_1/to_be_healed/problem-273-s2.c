#include <stdlib.h>

int *subtract_tuples(const int *t1, const int *t2, size_t size) {
    if (t1 == NULL || t2 == NULL) {
        return NULL;
    }
    
    int *result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < size; ++i) {
        result[i] = t1[i] - t2[i];
    }
    
    return result;
}

int main(void) {
    int tuple1[] = {10, 20, 30, 40, 50};
    /* Possible weaknesses found:
     *  Variable 'tuple2' can be declared as const array [constVariable]
     */
    int tuple2[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(tuple1) / sizeof(tuple1[0]);
    
    int *result = subtract_tuples(tuple1, tuple2, size);
    if (result == NULL) {
        return 1;
    }
    
    free(result);
    return 0;
}