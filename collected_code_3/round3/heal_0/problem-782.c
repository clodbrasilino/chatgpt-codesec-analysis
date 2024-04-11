#include <stdio.h>

int sumOddLengthSubarrays(int* arr, int arrSize){
    int total = 0;
    for (int i = 0; i < arrSize; i++) {
        for (int j = i; j < arrSize; j+=2) {
            for (int k = i; k <= j; k++) {
                total += arr[k];
            }
        }
    }
    return total;
}

int main() {
    int arr[] = {1, 4, 2, 5, 3};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int sum = sumOddLengthSubarrays(arr, arrSize);
    printf("Sum of all odd length subarrays is %d\n", sum);
    return 0;
}