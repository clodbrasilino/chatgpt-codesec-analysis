#include <stdio.h>
#include <limits.h>

int maxSubArraySum(const int arr[], int n, int *start, int *end) {
    int maxSoFar = INT_MIN, maxEndingHere = 0;
    *start = *end = 0;
    int s = 0;

    for (int i = 0; i < n; i++) {
        maxEndingHere += arr[i];
        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
            *start = s;
            *end = i;
        }
        if (maxEndingHere < 0) {
            maxEndingHere = 0;
            s = i + 1;
        }
    }

    return maxSoFar;
}

int main() {
    const int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int start, end;
    int maxSum = maxSubArraySum(arr, n, &start, &end);

    printf("Maximum sum of subarray: %d\n", maxSum);
    printf("Length of the subarray: %d\n", (end - start + 1));

    return 0;
}