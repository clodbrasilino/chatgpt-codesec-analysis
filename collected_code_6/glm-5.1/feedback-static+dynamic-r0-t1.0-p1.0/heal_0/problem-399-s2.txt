#include <stdio.h>
#include <stdlib.h>

size_t xor_tuples(int **tuples, size_t num_tuples, size_t tuple_size, int **result) {
    if (tuples == NULL || result == NULL || num_tuples == 0 || tuple_size == 0) {
        return 0;
    }

    *result = (int *)malloc(tuple_size * sizeof(int));
    if (*result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < tuple_size; i++) {
        (*result)[i] = 0;
        for (size_t j = 0; j < num_tuples; j++) {
            if (tuples[j] == NULL) {
                free(*result);
                *result = NULL;
                return 0;
            }
            (*result)[i] ^= tuples[j][i];
        }
    }

    return tuple_size;
}

int main(void) {
    int t0[] = {10, 20, 30};
    int t1[] = {5, 15, 25};
    int t2[] = {12, 22, 32};

    int *tuples[] = {t0, t1, t2};
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t tuple_size = sizeof(t0) / sizeof(t0[0]);

    int *result = NULL;
    size_t result_size = xor_tuples(tuples, num_tuples, tuple_size, &result);

    if (result_size > 0 && result != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
        result = NULL;
    } else {
        printf("Failed to compute XOR.\n");
    }

    return 0;
}