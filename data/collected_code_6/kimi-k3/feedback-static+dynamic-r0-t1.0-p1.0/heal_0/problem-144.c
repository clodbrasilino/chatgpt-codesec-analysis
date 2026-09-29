#include <stdio.h>
#include <stdlib.h>

long long sumAbsoluteDifferences(const int arr[], size_t n) {
    long long sum = 0;
    size_t i, j;
    
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            sum += llabs((long long)arr[i] - (long long)arr[j]);
        }
    }
    
    return sum;
}

int main(void) {
    int arr[] = {1, 4, 2, 8, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;
    
    result = sumAbsoluteDifferences(arr, n);
    
    printf("Sum of absolute differences: %lld\n", result);
    
    return 0;
}