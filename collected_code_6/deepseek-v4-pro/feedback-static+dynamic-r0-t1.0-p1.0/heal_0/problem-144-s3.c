#include <stdio.h>
#include <stdlib.h>

long long sum_absolute_differences(int *arr, int n) {
    long long sum = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sum += llabs((long long)arr[i] - arr[j]);
        }
    }
    
    return sum;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    long long result = sum_absolute_differences(arr, n);
    printf("Sum of absolute differences: %lld\n", result);
    
    return 0;
}