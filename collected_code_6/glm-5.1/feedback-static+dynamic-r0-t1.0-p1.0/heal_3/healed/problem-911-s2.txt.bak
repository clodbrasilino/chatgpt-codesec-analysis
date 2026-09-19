#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long maximumProduct(const int *nums, int numsSize) {
    if (numsSize < 3) return 0;
    
    long long max1 = LLONG_MIN, max2 = LLONG_MIN, max3 = LLONG_MIN;
    long long min1 = LLONG_MAX, min2 = LLONG_MAX;

    for (int i = 0; i < numsSize; i++) {
        long long val = nums[i];
        if (val >= max1) {
            max3 = max2;
            max2 = max1;
            max1 = val;
        } else if (val >= max2) {
            max3 = max2;
            max2 = val;
        } else if (val > max3) {
            max3 = val;
        }

        if (val <= min1) {
            min2 = min1;
            min1 = val;
        } else if (val <= min2) {
            min2 = val;
        }
    }

    long long product1 = max1 * max2 * max3;
    long long product2 = max1 * min1 * min2;

    return product1 > product2 ? product1 : product2;
}

int main() {
    int arr1[] = {1, 2, 3, 4};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%lld\n", maximumProduct(arr1, size1));

    int arr2[] = {-10, -10, 5, 2};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%lld\n", maximumProduct(arr2, size2));

    int arr3[] = {-5, -6, -1, -2, -3};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%lld\n", maximumProduct(arr3, size3));

    return 0;
}