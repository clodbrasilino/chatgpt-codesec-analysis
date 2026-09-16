#include <stdio.h>

int sumOddLengthSubarrays(int *arr, int n) {
    int sum = 0;
    for (int start = 0; start < n; ++start) {
        for (int length = 1; start + length <= n; length += 2) {
            for (int i = start; i < start + length; ++i) {
                sum += arr[i];
            }
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 4, 2, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = sumOddLengthSubarrays(arr, n);
    printf("Sum of all odd length subarrays: %d\n", result);
    return 0;
}