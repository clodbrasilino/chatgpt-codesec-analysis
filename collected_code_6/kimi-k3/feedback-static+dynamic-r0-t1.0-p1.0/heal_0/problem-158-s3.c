#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int min_operations_to_equal(int *arr, size_t n, int k) {
    if (arr == NULL || n == 0 || k <= 0) {
        return -1;
    }
    
    qsort(arr, n, sizeof(int), compare_ints);
    
    int target = arr[0];
    int operations = 0;
    
    for (size_t i = 1; i < n; i++) {
        int diff = arr[i] - target;
        if (diff % k != 0) {
            return -1;
        }
        int ops = diff / k;
        if (ops > INT_MAX - operations) {
            return -1;
        }
        operations += ops;
    }
    
    return operations;
}

int main(void) {
    int arr1[] = {4, 7, 10, 13};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 3;
    int result1 = min_operations_to_equal(arr1, n1, k1);
    if (result1 != -1) {
        printf("Minimum operations: %d\n", result1);
    } else {
        printf("Impossible to make all elements equal\n");
    }
    
    int arr2[] = {1, 2, 3};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 2;
    int result2 = min_operations_to_equal(arr2, n2, k2);
    if (result2 != -1) {
        printf("Minimum operations: %d\n", result2);
    } else {
        printf("Impossible to make all elements equal\n");
    }
    
    return 0;
}