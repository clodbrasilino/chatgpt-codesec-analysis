#include <stdio.h>
#include <limits.h>

int findMaxDifference(int arr[], int n) {
    int minElement = INT_MAX;
    int maxDifference = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < minElement) {
            minElement = arr[i];
        }
        if (arr[i] - minElement > maxDifference) {
            maxDifference = arr[i] - minElement;
        }
    }
    return maxDifference;
}

int main() {
    int arr[] = {2, 3, 10, 6, 4, 8, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findMaxDifference(arr, n);
    printf("Maximum difference: %d\n", result);
    return 0;
}