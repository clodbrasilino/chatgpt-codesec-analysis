#include <stdio.h>
#include <stdlib.h>

long long sumOfProductsOfSubarrays(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long totalSum = 0;

    for (size_t i = 0; i < n; i++) {
        long long currentProduct = 1;
        for (size_t j = i; j < n; j++) {
            currentProduct *= arr[j];
            totalSum += currentProduct;
        }
    }

    return totalSum;
}

int main(void) {
    int arr[] = {1, 2, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    long long result = sumOfProductsOfSubarrays(arr, n);

    printf("%lld\n", result);

    return 0;
}