#include <stdio.h>
#include <stdlib.h>

int compare_desc(const void *a, const void *b) {
    double diff = *(const double *)b - *(const double *)a;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

double *get_n_largest(const double *dataset, size_t dataset_size, size_t n) {
    if (dataset == NULL || dataset_size == 0 || n == 0 || n > dataset_size) {
        return NULL;
    }

    double *copy = malloc(dataset_size * sizeof(double));
    if (copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < dataset_size; ++i) {
        copy[i] = dataset[i];
    }

    qsort(copy, dataset_size, sizeof(double), compare_desc);

    double *result = malloc(n * sizeof(double));
    if (result == NULL) {
        free(copy);
        return NULL;
    }

    for (size_t i = 0; i < n; ++i) {
        result[i] = copy[i];
    }

    free(copy);
    return result;
}

int main(void) {
    double data[] = {3.5, 1.2, 9.8, 2.2, 7.7, 4.4, 8.1, 0.5};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    size_t n = 3;

    double *largest = get_n_largest(data, data_size, n);
    if (largest == NULL) {
        fprintf(stderr, "Error: invalid input or allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        printf("%.2f\n", largest[i]);
    }

    free(largest);
    return EXIT_SUCCESS;
}