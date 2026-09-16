#include <stdio.h>
#include <stdlib.h>

int* multiply_adjacent(const int* tuple, size_t size, size_t* out_size) {
    if (tuple == NULL || out_size == NULL || size == 0) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    if (size == 1) {
        *out_size = 0;
        return NULL;
    }

    *out_size = size - 1;
    int* result = (int*)malloc(*out_size * sizeof(int));
    
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_size; i++) {
        result[i] = tuple[i] * tuple[i + 1];
    }

    return result;
}

int main(void) {
    int tuple[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    size_t out_size = 0;

    int* result = multiply_adjacent(tuple, size, &out_size);

    if (result != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Failed to compute or array too small.\n");
    }

    return 0;
}