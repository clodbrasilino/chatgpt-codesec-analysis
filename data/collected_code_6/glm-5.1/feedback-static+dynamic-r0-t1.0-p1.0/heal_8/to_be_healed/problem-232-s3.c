#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_doubles(const void *a, const void *b) {
    double val_a = *(const double *)a;
    double val_b = *(const double *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

double *get_n_largest(const double *dataset, size_t dataset_size, size_t n, size_t *out_size) {
    if (dataset == NULL || out_size == NULL) {
        return NULL;
    }
    
    *out_size = 0;
    
    if (n == 0 || dataset_size == 0) {
        return NULL;
    }

    size_t m = (n < dataset_size) ? n : dataset_size;
    
    if (dataset_size > SIZE_MAX / sizeof(double)) {
        return NULL;
    }

    size_t total_bytes = dataset_size * sizeof(double);

    double *sorted = (double *)malloc(total_bytes);
    if (sorted == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, dataset, total_bytes);

    qsort(sorted, dataset_size, sizeof(double), compare_doubles);

    double *result = (double *)malloc(m * sizeof(double));
    if (result == NULL) {
        free(sorted);
        return NULL;
    }

    for (size_t i = 0; i < m; i++) {
        result[i] = sorted[dataset_size - 1 - i];
    }

    free(sorted);
    *out_size = m;
    return result;
}

int main(void) {
    double data[] = {3.5, 1.2, 7.8, 4.4, 9.1, 2.9, 6.6};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    size_t n = 4;
    size_t out_size = 0;

    double *largest = get_n_largest(data, data_size, n, &out_size);

    if (largest != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%f ", largest[i]);
        }
        printf("\n");
        free(largest);
    } else if (out_size == 0) {
        printf("Failed to allocate memory or empty dataset.\n");
    }

    return 0;
}