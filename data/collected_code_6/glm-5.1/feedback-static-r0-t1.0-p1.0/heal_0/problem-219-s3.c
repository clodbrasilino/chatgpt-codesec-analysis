#include <stdio.h>
#include <stdlib.h>

void extract_min_max_k(int *tuple, size_t tuple_size, size_t k, int **min_k, int **max_k) {
    if (tuple == NULL || min_k == NULL || max_k == NULL || tuple_size == 0) {
        return;
    }

    if (k > tuple_size) {
        k = tuple_size;
    }

    int *asc = malloc(tuple_size * sizeof(int));
    if (asc == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple_size; i++) {
        asc[i] = tuple[i];
    }

    for (size_t i = 0; i < tuple_size; i++) {
        for (size_t j = i + 1; j < tuple_size; j++) {
            if (asc[i] > asc[j]) {
                int temp = asc[i];
                asc[i] = asc[j];
                asc[j] = temp;
            }
        }
    }

    *min_k = malloc(k * sizeof(int));
    if (*min_k == NULL) {
        free(asc);
        return;
    }

    for (size_t i = 0; i < k; i++) {
        (*min_k)[i] = asc[i];
    }

    *max_k = malloc(k * sizeof(int));
    if (*max_k == NULL) {
        free(asc);
        free(*min_k);
        *min_k = NULL;
        return;
    }

    for (size_t i = 0; i < k; i++) {
        (*max_k)[i] = asc[tuple_size - k + i];
    }

    free(asc);
}

int main(void) {
    int tuple[] = {13, 5, 2, 8, 19, 1, 7, 11};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    size_t k = 3;

    int *min_k = NULL;
    int *max_k = NULL;

    extract_min_max_k(tuple, tuple_size, k, &min_k, &max_k);

    if (min_k != NULL && max_k != NULL) {
        printf("Min %zu elements: ", k);
        for (size_t i = 0; i < k; i++) {
            printf("%d ", min_k[i]);
        }
        printf("\n");

        printf("Max %zu elements: ", k);
        for (size_t i = 0; i < k; i++) {
            printf("%d ", max_k[i]);
        }
        printf("\n");
    }

    free(min_k);
    free(max_k);

    return 0;
}