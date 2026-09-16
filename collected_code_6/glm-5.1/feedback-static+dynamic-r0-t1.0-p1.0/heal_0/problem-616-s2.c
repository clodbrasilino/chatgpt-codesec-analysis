#include <stdio.h>
#include <stdlib.h>

int* tuple_modulo(const int* tuple1, const int* tuple2, size_t size) {
    if (tuple1 == NULL || tuple2 == NULL || size == 0) {
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
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
    int t1[] = {10, 20, 30, 40, 50};
    int t2[] = {3, 4, 5, 6, 7};
    size_t size = sizeof(t1) / sizeof(t1[0]);

    int* res = tuple_modulo(t1, t2, size);
    if (res == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);

    return EXIT_SUCCESS;
}