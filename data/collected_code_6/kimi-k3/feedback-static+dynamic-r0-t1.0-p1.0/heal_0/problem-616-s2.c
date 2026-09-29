#include <stdio.h>
#include <stdlib.h>

int* modulo_tuples(const int *tuple1, const int *tuple2, size_t size) {
    if (tuple1 == NULL || tuple2 == NULL || size == 0) {
        return NULL;
    }

    int *result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple2[i] == 0) {
            free(result);
            return NULL;
        }
        result[i] = tuple1[i] % tuple2[i];
    }

    return result;
}

int main(void) {
    int tuple1[] = {10, 20, 30, 40};
    int tuple2[] = {3, 4, 5, 6};
    size_t size = sizeof(tuple1) / sizeof(tuple1[0]);

    int *result = modulo_tuples(tuple1, tuple2, size);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Operation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: (");
    for (size_t i = 0; i < size; i++) {
        printf("%d", result[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free(result);
    return EXIT_SUCCESS;
}