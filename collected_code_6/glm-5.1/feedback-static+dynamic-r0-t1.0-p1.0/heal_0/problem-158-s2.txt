#include <stdio.h>
#include <stdlib.h>

int find_min_operations(int *arr, int n, int k) {
    if (arr == NULL || n <= 0 || k <= 0) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int min_ops = 0;
    for (int i = 0; i < k; i++) {
        min_ops += arr[n - 1] - arr[i];
    }

    return min_ops;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 3;
    int result1 = find_min_operations(arr1, n1, k1);
    printf("%d\n", result1);

    int arr2[] = {10, 20, 30};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 2;
    int result2 = find_min_operations(arr2, n2, k2);
    printf("%d\n", result2);

    return 0;
}