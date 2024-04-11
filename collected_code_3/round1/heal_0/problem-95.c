#include <stdio.h>
#include <limits.h>

int findMinLength(int arr[], int n, int x) {
    int minLength = INT_MAX;
    int currentSum = 0;
    int start = 0;

    for (int end = 0; end < n; end++) {
        currentSum += arr[end];

        while (currentSum > x && start < n) {
            if (end - start + 1 < minLength) {
                minLength = end - start + 1;
            }
            currentSum -= arr[start];
            start++;
        }
    }

    if (minLength == INT_MAX) {
        return -1;
    }

    return minLength;
}

int main() {
    int arr[] = {1, 4, 45, 6, 0, 19};
    int x = 51;
    int n = sizeof(arr) / sizeof(arr[0]);
    int res = findMinLength(arr, n, x);
    if (res == -1) {
        printf("No sublist found\n");
    } else {
        printf("Minimum length of sublist is %d\n", res);
    }
    return 0;
}