#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void counting_sort(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int range = max - min + 1;
    int *count = (int *)calloc((size_t)range, sizeof(int));
    if (count == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    int *output = (int *)malloc((size_t)n * sizeof(int));
    if (output == NULL) {
        free(count);
        return;
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    size_t total_size = (size_t)n * sizeof(int);
    if (output != NULL && arr != NULL) {
        memmove(arr, output, total_size);
    }

    free(output);
    free(count);
}

int main(void) {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    counting_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}