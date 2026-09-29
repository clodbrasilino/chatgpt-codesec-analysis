#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long adjacentElementsProduct(const int* inputArray, size_t size) {
    if (inputArray == NULL || size < 2) {
        return LLONG_MIN;
    }

    long long max_product = (long long)inputArray[0] * inputArray[1];

    for (size_t i = 1; i < size - 1; ++i) {
        long long current_product = (long long)inputArray[i] * inputArray[i + 1];
        if (current_product > max_product) {
            max_product = current_product;
        }
    }

    return max_product;
}

int main(void) {
    int arr1[] = {3, 6, -2, -5, 7, 3};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    long long result1 = adjacentElementsProduct(arr1, size1);
    if (result1 != LLONG_MIN) {
        printf("%lld\n", result1);
    }

    int arr2[] = {-1, -2};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    long long result2 = adjacentElementsProduct(arr2, size2);
    if (result2 != LLONG_MIN) {
        printf("%lld\n", result2);
    }
    
    int arr3[] = {5, 1, 2, 3, 1, 4};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    long long result3 = adjacentElementsProduct(arr3, size3);
    if (result3 != LLONG_MIN) {
        printf("%lld\n", result3);
    }

    return 0;
}