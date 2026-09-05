#include <stdio.h>
#include <stdlib.h>

int compare_desc(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    if (int_a < int_b) return 1;
    if (int_a > int_b) return -1;
    return 0;
}

int *get_n_largest(const int *dataset, size_t dataset_len, size_t n) {
    if (dataset == NULL || n == 0 || n > dataset_len) {
        return NULL;
    }

    int *copy = malloc(dataset_len * sizeof(int));
    if (copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < dataset_len; i++) {
        copy[i] = dataset[i];
    }

    qsort(copy, dataset_len, sizeof(int), compare_desc);

    int *result = malloc(n * sizeof(int));
    if (result == NULL) {
        free(copy);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        result[i] = copy[i];
    }

    free(copy);
    return result;
}

int main(void) {
    int data[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 3;

    int *largest = get_n_largest(data, data_len, n);
    if (largest == NULL) {
        return EXIT_FAILURE;
    }

    printf("The %zu largest items are: ", n);
    for (size_t i = 0; i < n; i++) {
        printf("%d ", largest[i]);
    }
    printf("\n");

    free(largest);

    return EXIT_SUCCESS;
}