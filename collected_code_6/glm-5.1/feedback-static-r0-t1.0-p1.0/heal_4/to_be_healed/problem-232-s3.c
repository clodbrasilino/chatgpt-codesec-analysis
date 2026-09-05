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
    if (out_size == NULL) {
        return NULL;
    }
    
    *out_size = 0;
    
    if (dataset == NULL || dataset_size == 0 || n == 0) {
        return NULL;
    }

    size_t m = (n < dataset_size) ? n : dataset_size;
    
    qsort((double *)dataset, dataset_size, sizeof(double), compare_doubles);

    double *result = (double *)malloc(m * sizeof(double));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < m; i++) {
        result[i] = dataset[dataset_size - 1 - i];
    }

    *out_size = m;
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <data_size> <n>\n", argv[0]);
        return 1;
    }

    size_t data_size = (size_t)strtoull(argv[1], NULL, 10);
    size_t n = (size_t)strtoull(argv[2], NULL, 10);

    double *data = (double *)malloc(data_size * sizeof(double));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (size_t i = 0; i < data_size; i++) {
        if (scanf("%lf", &data[i]) != 1) {
            free(data);
            return 1;
        }
    }

    size_t out_size = 0;
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

    free(data);
    return 0;
}