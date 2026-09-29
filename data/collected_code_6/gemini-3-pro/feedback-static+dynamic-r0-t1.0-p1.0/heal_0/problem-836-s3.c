#include <stdio.h>
#include <stdlib.h>

int maxSubArrayLength(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int maxSum = arr[0];
    int currentSum = arr[0];
    int maxLength = 1;
    int currentLength = 1;
    int maxStart = 0;
    int maxEnd = 0;
    int currentStart = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] > currentSum + arr[i]) {
            currentSum = arr[i];
            currentStart = i;
            currentLength = 1;
        } else {
            currentSum = currentSum + arr[i];
            currentLength++;
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            maxStart = currentStart;
            maxEnd = i;
            maxLength = currentLength;
        } else if (currentSum == maxSum) {
            if (currentLength > maxLength) {
                maxLength = currentLength;
                maxStart = currentStart;
                maxEnd = i;
            }
        }
    }

    return maxLength;
}

int main(void) {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int length = maxSubArrayLength(arr, n);

    printf("Length of the subarray with maximum sum: %d\n", length);

    return 0;
}