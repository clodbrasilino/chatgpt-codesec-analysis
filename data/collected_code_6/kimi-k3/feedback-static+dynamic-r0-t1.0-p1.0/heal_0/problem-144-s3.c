#include <stdio.h>
#include <stdlib.h>

long long sumOfAbsoluteDifferences(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    long long sum = 0;
    
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            long long diff = (long long)arr[i] - (long long)arr[j];
            sum += (diff < 0) ? -diff : diff;
        }
    }
    
    return sum;
}

int main(void) {
    int arr[] = {1, 4, 2, 8, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    long long result = sumOfAbsoluteDifferences(arr, n);
    
    if (printf("Sum of absolute differences: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}