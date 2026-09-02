#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int *get_n_smallest(const int *data, size_t data_size, size_t n, size_t *result_size) {
    if (data == NULL || data_size == 0 || n == 0 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    if (n > data_size) {
        n = data_size;
    }

    int *sorted = malloc(data_size * sizeof(*sorted));
    if (sorted == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    for (size_t i = 0; i < data_size; i++) {
        sorted[i] = data[i];
    }

    qsort(sorted, data_size, sizeof(*sorted), compare_ints);

    int *result = malloc(n * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        result[i] = sorted[i];
    }

    free(sorted);
    *result_size = n;
    return result;
}

int main(void) {
    int dataset[] = {42, 17, 23, 8, 31, 5, 29, 11, 19, 47};
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    size_t result_size = 0;

    int *smallest = get_n_smallest(dataset, dataset_size, n, &result_size);

    if (smallest == NULL) {
        fprintf(stderr, "Failed to retrieve smallest items\n");
        return EXIT_FAILURE;
    }

    printf("The %zu smallest items are: ", result_size);
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");

    free(smallest);
    return EXIT_SUCCESS;
}