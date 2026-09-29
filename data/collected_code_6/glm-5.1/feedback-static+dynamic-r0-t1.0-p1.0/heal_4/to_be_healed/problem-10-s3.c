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
    /* Possible weaknesses found:
     *  Assignment 'data_len=sizeof(data)/sizeof(data[0])', assigned value is 10
     */
    size_t data_len = sizeof(data) / sizeof(data[0]);
    /* Possible weaknesses found:
     *  Assignment 'n=4', assigned value is 4
     */
    size_t n = 4;

    /* Possible weaknesses found:
     *  Condition 'n==0' is always false [knownConditionTrueFalse]
     *  Condition 'n==0' is always false
     *  Condition 'data_len==0' is always false [knownConditionTrueFalse]
     *  Condition 'data_len==0' is always false
     */
    if (data_len == 0 || n == 0) {
        return 0;
    }

    int *smallest = get_n_smallest(data, data_len, n);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (smallest == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     *  Assignment 'actual_n=n', assigned value is 4
     *  actual_n is assigned 'n' here.
     */
    size_t actual_n = n;
    /* Possible weaknesses found:
     *  Condition 'n>data_len' is always false [knownConditionTrueFalse]
     *  Condition 'n>data_len' is always false
     */
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