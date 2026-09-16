#include <stdio.h>
#include <stdlib.h>

int find_k_operations(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    int k = 0;
    for (int i = 0; i < n / 2; i++) {
        k += arr[n - 1 - i] - arr[i];
    }
    return k;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    int result = find_k_operations(arr, n);
    printf("%d\n", result);
    free(arr);
    return 0;
}