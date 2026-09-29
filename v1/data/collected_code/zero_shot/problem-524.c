#include<stdio.h>

int findMaxSum(int arr[], int n) {
    int maxSum = 0; // maximum sum of increasing subsequence
    int currentSum = 0; // current sum of increasing subsequence

    for (int i = 0; i < n; i++) {
        if (i > 0 && arr[i] > arr[i-1]) {
            // Element is part of increasing subsequence, add it to currentSum
            currentSum += arr[i];
        } else {
            // Element is not part of increasing subsequence
            // Update maxSum if currentSum is greater
            if (currentSum > maxSum) {
                maxSum = currentSum;
            }
            // Start new increasing subsequence
            currentSum = arr[i];
        }
    }

    // Check if the last increasing subsequence has maximum sum
    if (currentSum > maxSum) {
        maxSum = currentSum;
    }

    return maxSum;
}

int main() {
    int arr[] = {1, 2, 3, 1, 5, 7, 9, 2, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int maxSum = findMaxSum(arr, n);

    printf("Maximum sum of increasing subsequence is %d\n", maxSum);

    return 0;
}