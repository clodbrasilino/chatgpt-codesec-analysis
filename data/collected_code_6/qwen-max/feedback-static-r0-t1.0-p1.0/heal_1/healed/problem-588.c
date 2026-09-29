#include <stdio.h>
#include <limits.h>

int findDifference(const int arr[], int n) {
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max - min;
}

int main() {
    const int arr[] = {3, 1, 9, 7, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findDifference(arr, n);
    printf("Difference: %d\n", result);
    return 0;
}