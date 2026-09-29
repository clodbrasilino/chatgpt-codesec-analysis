#include <stdio.h>
#include <stdlib.h>

void tuple_modulo(size_t len, const int *tuple1, const int *tuple2, int *result) {
    for (size_t i = 0; i < len; ++i) {
        if (tuple2[i] != 0) {
            result[i] = tuple1[i] % tuple2[i];
        } else {
            fprintf(stderr, "Error: Division by zero at index %zu\n", i);
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    int tuple1[] = {10, 25, 30};
    const int tuple2[] = {3, 5, 7};
    size_t len = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result = malloc(len * sizeof(int));

    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    tuple_modulo(len, tuple1, tuple2, result);

    for (size_t i = 0; i < len; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}