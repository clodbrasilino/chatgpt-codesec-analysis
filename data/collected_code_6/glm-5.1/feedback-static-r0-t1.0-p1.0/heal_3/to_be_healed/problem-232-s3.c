#include <stdio.h>
#include <stdlib.h>

int compare_doubles(const void *a, const void *b) {
    double val_a = *(const double *)a;
    double val_b = *(const double *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

double *get_n_largest(const double *dataset, size_t dataset_size, size_t n, size_t *out_size) {
    if (dataset == NULL || out_size == NULL || dataset_size == 0) {
        if (out_size != NULL) *out_size = 0;
        return NULL;
    }
    
    if (n == 0) {
        *out_size = 0;
        return NULL;
    }

    size_t m = (n < dataset_size) ? n : dataset_size;
    
    double *sorted = (double *)malloc(dataset_size * sizeof(double));
    if (sorted == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < dataset_size; i++) {
        sorted[i] = dataset[i];
    }

    qsort(sorted, dataset_size, sizeof(double), compare_doubles);

    double *result = (double *)malloc(m * sizeof(double));
    if (result == NULL) {
        free(sorted);
        *out_size = 0;
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
    /* Possible weaknesses found:
     *  Assignment 'data_size=sizeof(data)/sizeof(data[0])', assigned value is 7
     */
    size_t data_size = sizeof(data) / sizeof(data[0]);
    /* Possible weaknesses found:
     *  Assignment 'n=4', assigned value is 4
     */
    size_t n = 4;
    size_t out_size = 0;

    double *largest = get_n_largest(data, data_size, n, &out_size);

    if (largest != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%f ", largest[i]);
        }
        printf("\n");
        free(largest);
    /* Possible weaknesses found:
     *  Condition 'data_size>0' is always true
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     *  Condition 'data_size>0' is always true [knownConditionTrueFalse]
     */
    } else if (out_size == 0 && n > 0 && data_size > 0) {
        printf("Failed to allocate memory or empty dataset.\n");
    }

    return 0;
}