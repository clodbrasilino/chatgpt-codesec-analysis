#include <stdio.h>

int sumOddLengthSubarrays(int* arr, int arrSize) {
    int sum = 0;
    
    for (int i = 0; i < arrSize; i++) {
        for (int j = i; j < arrSize; j += 2) {
            for (int k = i; k <= j; k++) {
                sum += arr[k];
            }
        }
    }
    
    return sum;
}

int main() {
    int arr[] = {1, 4, 2, 5, 3};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    
    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("Sum of all odd length subarrays: %d\n", result);
    
    return 0;
}