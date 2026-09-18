#include <stdio.h>
#include <stdlib.h>

int maxSubArrayLength(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int maxSum = arr[0];
    int currentSum = arr[0];
    int maxLength = 1;
    int currentLength = 1;

    for (int i = 1; i < n; i++) {
        if (currentSum < 0) {
            currentSum = arr[i];
            currentLength = 1;
        } else {
            currentSum = currentSum + arr[i];
            currentLength++;
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            maxLength = currentLength;
        } else if (currentSum == maxSum) {
            if (currentLength > maxLength) {
                maxLength = currentLength;
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