#include <stdio.h>
#include <stdlib.h>

int compare_int(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    if (int_a < int_b) {
        return -1;
    }
    if (int_a > int_b) {
        return 1;
    }
    return 0;
}

int* get_n_largest(const int *dataset, size_t dataset_size, size_t n, size_t *out_size) {
    if (dataset == NULL || out_size == NULL || dataset_size == 0 || n == 0) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t actual_n = (n > dataset_size) ? dataset_size : n;
    int *result = (int *)malloc(actual_n * sizeof(int));
    
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < actual_n; i++) {
        result[i] = dataset[i];
    }

    qsort(result, actual_n, sizeof(int), compare_int);

    for (size_t i = actual_n; i < dataset_size; i++) {
        if (dataset[i] > result[0]) {
            result[0] = dataset[i];
            size_t j = 0;
            while (j < actual_n - 1 && result[j] > result[j + 1]) {
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
                j++;
            }
        }
    }

    *out_size = actual_n;
    return result;
}

int main(void) {
    const int dataset[] = {45, 2, 89, 12, 7, 99, 43, 22, 105, 1, 8};
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;
    size_t returned_size = 0;

    int *largest_items = get_n_largest(dataset, dataset_size, n, &returned_size);

    if (largest_items != NULL) {
        for (size_t i = 0; i < returned_size; i++) {
            printf("%d\n", largest_items[i]);
        }
        free(largest_items);
        largest_items = NULL;
    }

    return 0;
}