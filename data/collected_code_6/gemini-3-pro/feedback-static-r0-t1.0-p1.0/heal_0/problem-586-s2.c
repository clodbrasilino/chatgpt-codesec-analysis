#include <stdio.h>
#include <stdlib.h>

void split_and_add(int* arr, size_t n, size_t k) {
    if (arr == NULL || n == 0 || k == 0 || k >= n) {
        return;
    }

    int* temp = (int*)malloc(k * sizeof(int));
    if (temp == NULL) {
        return;
    }

    for (size_t i = 0; i < k; ++i) {
        temp[i] = arr[i];
    }

    for (size_t i = 0; i < n - k; ++i) {
        arr[i] = arr[i + k];
    }

    for (size_t i = 0; i < k; ++i) {
        arr[n - k + i] = temp[i];
    }

    free(temp);
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 2;

    split_and_add(arr, n, k);

    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}