#include <stdio.h>
#include <stdlib.h>

void rotate_right(int *arr, int n, int k) {
    k = k % n;
    if (k == 0) return;

    int *temp = (int *)malloc(k * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < k; ++i) {
        temp[i] = arr[n - k + i];
    }

    for (int i = n - 1; i >= k; --i) {
        arr[i] = arr[i - k];
    }

    for (int i = 0; i < k; ++i) {
        arr[i] = temp[i];
    }

    free(temp);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    rotate_right(arr, n, k);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}