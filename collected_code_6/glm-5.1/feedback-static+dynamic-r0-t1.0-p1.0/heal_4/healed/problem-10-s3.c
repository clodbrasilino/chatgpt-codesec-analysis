#include <stdio.h>
#include <stdlib.h>

void heapify(int *arr, size_t n, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

int *get_n_smallest(const int *dataset, size_t dataset_len, size_t *n) {
    if (dataset == NULL || dataset_len == 0 || *n == 0) {
        *n = 0;
        return NULL;
    }

    if (*n > dataset_len) {
        *n = dataset_len;
    }

    size_t actual_n = *n;

    int *result = (int *)malloc(actual_n * sizeof(int));
    if (result == NULL) {
        *n = 0;
        return NULL;
    }

    for (size_t i = 0; i < actual_n; i++) {
        result[i] = dataset[i];
    }

    for (size_t i = actual_n / 2; i > 0; i--) {
        heapify(result, actual_n, i - 1);
    }
    heapify(result, actual_n, 0);

    for (size_t i = actual_n; i < dataset_len; i++) {
        if (dataset[i] < result[0]) {
            result[0] = dataset[i];
            heapify(result, actual_n, 0);
        }
    }

    for (size_t i = actual_n - 1; i > 0; i--) {
        int temp = result[0];
        result[0] = result[i];
        result[i] = temp;
        heapify(result, i, 0);
    }

    return result;
}

int main(void) {
    int data[] = {12, 3, 5, 7, 19, 1, 8, 2, 10, 4};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 4;

    int *smallest = get_n_smallest(data, data_len, &n);

    if (smallest == NULL) {
        if (n == 0 && data_len > 0) {
            printf("Could not allocate memory.\n");
            return 1;
        }
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");

    free(smallest);
    smallest = NULL;

    return 0;
}