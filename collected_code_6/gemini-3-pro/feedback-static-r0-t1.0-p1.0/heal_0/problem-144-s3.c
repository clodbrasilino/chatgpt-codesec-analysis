#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long sum_of_absolute_differences(int* arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            sum += llabs((long long)arr[i] - (long long)arr[j]);
        }
    }
    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    long long result = sum_of_absolute_differences(arr, n);
    
    printf("Sum of absolute differences: %lld\n", result);

    return 0;
}