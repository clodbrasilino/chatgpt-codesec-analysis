#include <stdio.h>

int *multiply_adjacent_elements(int *arr, int size, int *result_size) {
    if (arr == NULL || size < 2) {
        *result_size = 0;
        return NULL;
    }

    int *result = (int *)malloc((size - 1) * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < size - 1; i++) {
        result[i] = arr[i] * arr[i + 1];
    }

    *result_size = size - 1;
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result_size = 0;

    int *result = multiply_adjacent_elements(arr, size, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}