#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t used;
    size_t size;
} Data;

Data* create_data(size_t initial_size) {
    Data *d = (Data *)malloc(sizeof(Data));
    d->data = (int *)malloc(initial_size * sizeof(int));
    d->used = 0;
    d->size = initial_size;
    return d;
}

void free_data(Data *d) {
    free(d->data);
    free(d);
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void get_n_smallest(int *arr, size_t arr_size, int *result, size_t n) {
    qsort(arr, arr_size, sizeof(int), compare);
    for (size_t i = 0; i < n; ++i) {
        result[i] = arr[i];
    }
}

int main() {
    int dataset[] = {4, 2, 9, 6, 23, 12, 34, 0, 1};
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;
    int *result = (int *)malloc(n * sizeof(int));

    if (result == NULL) {
        return 1;
    }

    get_n_smallest(dataset, dataset_size, result, n);

    for (size_t i = 0; i < n; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}