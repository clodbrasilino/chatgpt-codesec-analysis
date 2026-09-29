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
    
    double *sorted = (double *)malloc(dataset_size * sizeof(double));
    if (sorted == NULL) {
        return NULL;
    }

    memcpy(sorted, dataset, dataset_size * sizeof(double));

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
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'n' undeclared (first use in this function)
     *  use of undeclared identifier 'n'
     */
    scanf("%zu", &n);
    size_t out_size = 0;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'n'
     */
    double *largest = get_n_largest(data, data_size, n, &out_size);

    if (largest != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%f ", largest[i]);
        }
        printf("\n");
        free(largest);
    } else {
        printf("Failed to allocate memory or empty dataset.\n");
    }

    return 0;
}