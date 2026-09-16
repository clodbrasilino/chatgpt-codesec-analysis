#include <stdio.h>
#include <limits.h>

int maxSubarrayLength(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int maxSum = INT_MIN;
    int maxLen = 0;
    int currentSum = 0;
    int start = 0;
    int tempStart = 0;

    for (int i = 0; i < n; i++) {
        currentSum += arr[i];

        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = tempStart;
            maxLen = i - start + 1;
        } else if (currentSum == maxSum) {
            if (i - tempStart + 1 > maxLen) {
                start = tempStart;
                maxLen = i - start + 1;
            }
        }

        if (currentSum < 0) {
            currentSum = 0;
            tempStart = i + 1;
        }
    }

    return maxLen;
}

int main(void) {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int length = maxSubarrayLength(arr, n);

    printf("Length of subarray with maximum sum: %d\n", length);

    return 0;
}