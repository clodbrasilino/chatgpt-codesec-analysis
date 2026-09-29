#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    
    if (int_a == int_b) {
        return 0;
    }
    else if (int_a < int_b) {
        return -1;
    }
    else {
        return 1;
    }
}

int* get_n_smallest(const int* dataset, size_t dataset_size, size_t n) {
    if (dataset == NULL || n == 0 || n > dataset_size) {
        return NULL;
    }

    int* copy = (int*)malloc(dataset_size * sizeof(int));
    if (copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < dataset_size; ++i) {
        copy[i] = dataset[i];
    }

    qsort(copy, dataset_size, sizeof(int), compare_ints);

    int* result = (int*)malloc(n * sizeof(int));
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
    int dataset[] = {9, 4, 7, 1, 3, 8, 2, 5, 6};
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;

    int* smallest_items = get_n_smallest(dataset, dataset_size, n);
    if (smallest_items != NULL) {
        for (size_t i = 0; i < n; ++i) {
            printf("%d ", smallest_items[i]);
        }
        printf("\n");
        free(smallest_items);
    } else {
        printf("Failed to get smallest items.\n");
    }

    return 0;
}