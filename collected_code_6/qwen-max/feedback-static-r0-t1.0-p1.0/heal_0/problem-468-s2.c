#include <stdio.h>
#include <limits.h>

int maxProductSubsequence(int *arr, int n, int index, int prevIndex, int maxProduct) {
    if (index == n) return maxProduct;
    int notTake = maxProductSubsequence(arr, n, index + 1, prevIndex, maxProduct);
    int take = maxProduct;
    if (prevIndex == -1 || arr[index] > arr[prevIndex]) {
        take = maxProductSubsequence(arr, n, index + 1, index, (maxProduct ? maxProduct * arr[index] : arr[index]));
    }
    return (notTake > take) ? notTake : take;
}

int main() {
    int arr[] = {3, 100, 4, 5, 150, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum product: %d\n", maxProductSubsequence(arr, n, 0, -1, 0));
    return 0;
}