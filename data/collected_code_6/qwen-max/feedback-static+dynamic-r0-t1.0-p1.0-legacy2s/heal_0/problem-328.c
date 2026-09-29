#include <stdio.h>
#include <stdlib.h>

void rotate_left(int *arr, int n, int k) {
    k = k % n;
    if (k == 0) return;

    int *temp = (int *)malloc(k * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < k; ++i) {
        temp[i] = arr[i];
    }

    for (int i = k; i < n; ++i) {
        arr[i - k] = arr[i];
    }

    for (int i = 0; i < k; ++i) {
        arr[n - k + i] = temp[i];
    }

    free(temp);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    printf("Original array: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    rotate_left(arr, n, k);

    printf("Rotated array: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}