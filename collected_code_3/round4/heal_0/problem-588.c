#include <stdio.h>
#include <limits.h>

int findDifference(int arr[], int n) {
    int max = INT_MIN;
    int min = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    return max - min;
}

int main() {
    int arr[] = {12, 23, 34, 45, 56, 67, 78, 89, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Difference between largest and smallest value is %d", findDifference(arr, n));
    return 0;
}