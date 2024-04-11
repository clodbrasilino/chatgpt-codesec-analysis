#include <stdio.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

int min(int x, int y) {
    return (x < y) ? x : y;
}

int maxProduct(int arr[], int n) {
    int max_val = arr[0];
    int min_val = arr[0];
    int maxProduct = arr[0];
    int end_min, end_max;

    for (int i = 1; i < n; i++) {
        end_max = max_val * arr[i];
        end_min = min_val * arr[i];

        max_val = max(max(arr[i], end_max), end_min);
        min_val = min(min(arr[i], end_max), end_min);

        maxProduct = max(max_val, maxProduct);
    }

    return maxProduct;
}

int main() {
    int arr[] = {1, -2, -3, 0, 7, -8, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum Product is %d", maxProduct(arr, n));
    return 0;
}