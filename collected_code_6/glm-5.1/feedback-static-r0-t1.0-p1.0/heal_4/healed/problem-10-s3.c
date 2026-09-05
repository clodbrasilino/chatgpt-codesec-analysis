#include <stdio.h>
#include <stdlib.h>

int *get_n_smallest(const int *dataset, size_t dataset_len, size_t n) {
    if (dataset == NULL || dataset_len == 0 || n == 0) {
        return NULL;
    }

    size_t actual_n = n;
    if (n > dataset_len) {
        actual_n = dataset_len;
    }

    int *result = (int *)malloc(actual_n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < actual_n; i++) {
        result[i] = dataset[i];
    }

    for (size_t i = actual_n / 2; i > 0; i--) {
        size_t root = i;
        while (1) {
            size_t left = 2 * root;
            size_t right = 2 * root + 1;
            size_t largest = root;

            if (left <= actual_n && result[left - 1] > result[largest - 1]) {
                largest = left;
            }
            if (right <= actual_n && result[right - 1] > result[largest - 1]) {
                largest = right;
            }
            if (largest == root) {
                break;
            }

            int temp = result[root - 1];
            result[root - 1] = result[largest - 1];
            result[largest - 1] = temp;

            root = largest;
        }
    }

    for (size_t i = actual_n; i < dataset_len; i++) {
        if (dataset[i] < result[0]) {
            result[0] = dataset[i];

            size_t root = 1;
            while (1) {
                size_t left = 2 * root;
                size_t right = 2 * root + 1;
                size_t largest = root;

                if (left <= actual_n && result[left - 1] > result[largest - 1]) {
                    largest = left;
                }
                if (right <= actual_n && result[right - 1] > result[largest - 1]) {
                    largest = right;
                }
                if (largest == root) {
                    break;
                }

                int temp = result[root - 1];
                result[root - 1] = result[largest - 1];
                result[largest - 1] = temp;

                root = largest;
            }
        }
    }

    for (size_t i = actual_n - 1; i > 0; i--) {
        int temp = result[0];
        result[0] = result[i];
        result[i] = temp;

        size_t heap_size = i;
        size_t root = 1;
        while (1) {
            size_t left = 2 * root;
            size_t right = 2 * root + 1;
            size_t largest = root;

            if (left <= heap_size && result[left - 1] > result[largest - 1]) {
                largest = left;
            }
            if (right <= heap_size && result[right - 1] > result[largest - 1]) {
                largest = right;
            }
            if (largest == root) {
                break;
            }

            int temp2 = result[root - 1];
            result[root - 1] = result[largest - 1];
            result[largest - 1] = temp2;

            root = largest;
        }
    }

    return result;
}

int main(void) {
    int data[] = {12, 3, 5, 7, 19, 1, 8, 2, 10, 4};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 4;

    if (data_len == 0 || n == 0) {
        return 0;
    }

    int *smallest = get_n_smallest(data, data_len, n);
    if (smallest == NULL) {
        return 1;
    }

    size_t actual_n = n;
    if (n > data_len) {
        actual_n = data_len;
    }

    for (size_t i = 0; i < actual_n; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");

    free(smallest);
    smallest = NULL;

    return 0;
}