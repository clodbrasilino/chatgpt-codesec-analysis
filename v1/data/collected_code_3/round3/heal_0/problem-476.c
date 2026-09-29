#include <stdio.h>
#include <limits.h>

int findSum(int arr[], int n) {
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

    return max + min;
}

int main() {
    int arr[] = {12, 34, 56, 78, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Sum of largest and smallest value in the array is %d", findSum(arr, n));
    return 0;
}