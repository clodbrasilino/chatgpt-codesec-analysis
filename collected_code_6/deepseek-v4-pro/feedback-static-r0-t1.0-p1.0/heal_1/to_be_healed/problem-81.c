#include <stdio.h>
#include <stdlib.h>

int* zip_tuples(const int* tuple1, size_t size1, const int* tuple2, size_t size2, size_t* result_size) {
    if (tuple1 == NULL || tuple2 == NULL || result_size == NULL) {
        return NULL;
    }

    size_t max_size = size1 > size2 ? size1 : size2;
    *result_size = max_size * 2;

    int* result = (int*)malloc(*result_size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < max_size; i++) {
        if (i < size1) {
            result[i * 2] = tuple1[i];
        }
        if (i < size2) {
            result[i * 2 + 1] = tuple2[i];
        }
    }

    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'tuple1' can be declared as const array [constVariable]
     */
    int tuple1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'tuple2' can be declared as const array [constVariable]
     */
    int tuple2[] = {4, 5, 6, 7};
    size_t result_size = 0;

    int* zipped = zip_tuples(tuple1, 3, tuple2, 4, &result_size);

    if (zipped != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", zipped[i]);
        }
        printf("\n");
        free(zipped);
    }

    return 0;
}