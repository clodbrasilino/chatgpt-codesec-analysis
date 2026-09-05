#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void counting_sort(int arr[], int n) {
    if (arr == NULL || n <= 1) {
        return;
    }

    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    if (max < 0) {
        return;
    }

    size_t range = (size_t)max + 1;

    int *count = (int *)calloc(range, sizeof(int));
    if (count == NULL) {
        return;
    }

    int *output = (int *)malloc((size_t)n * sizeof(int));
    if (output == NULL) {
        free(count);
        return;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    for (size_t i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        count[arr[i]]--;
        output[count[arr[i]]] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

int main(void) {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    counting_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}