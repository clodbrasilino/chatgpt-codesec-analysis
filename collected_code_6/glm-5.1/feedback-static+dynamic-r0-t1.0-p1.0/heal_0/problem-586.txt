#include <stdio.h>
#include <stdlib.h>

void rotate(int *arr, int n, int k) {
    if (n <= 0) return;
    k = k % n;
    if (k < 0) k += n;
    if (k == 0) return;
    int *temp = (int *)malloc(k * sizeof(int));
    if (temp == NULL) return;
    for (int i = 0; i < k; i++) {
        temp[i] = arr[i];
    }
    for (int i = 0; i < n - k; i++) {
        arr[i] = arr[i + k];
    }
    for (int i = 0; i < k; i++) {
        arr[n - k + i] = temp[i];
    }
    free(temp);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    rotate(arr, n, k);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}