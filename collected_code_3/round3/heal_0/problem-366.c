#include <stdio.h>

int findLargestProduct(int arr[], int n) {
    int max_product = arr[0] * arr[1];
    for (int i = 1; i < n - 1; i++) {
        if (arr[i] * arr[i + 1] > max_product) {
            max_product = arr[i] * arr[i + 1];
        }
    }
    return max_product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Largest product of adjacent pairs is %d\n", findLargestProduct(arr, n));
    return 0;
}