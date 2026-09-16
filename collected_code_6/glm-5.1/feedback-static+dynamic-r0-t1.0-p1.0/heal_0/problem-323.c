#include <stdio.h>
#include <stdlib.h>

int* rearrange_alternating(int* arr, int n) {
    int* result = (int*)malloc(n * sizeof(int));
    if (!result) return NULL;

    int pos = 0;
    int neg = 0;

    for (int i = 0; i < n; i++) {
        while (pos < n && arr[pos] < 0) pos++;
        while (neg < n && arr[neg] >= 0) neg++;

        if (i % 2 == 0) {
            if (neg < n) {
                result[i] = arr[neg++];
            } else if (pos < n) {
                result[i] = arr[pos++];
            } else {
                result[i] = arr[--pos];
            }
        } else {
            if (pos < n) {
                result[i] = arr[pos++];
            } else if (neg < n) {
                result[i] = arr[neg++];
            } else {
                result[i] = arr[--neg];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        arr[i] = result[i];
    }

    free(result);
    return arr;
}

int main() {
    int arr[] = {2, 3, -4, -9, -1, 7, -6, -5, 8, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    rearrange_alternating(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}