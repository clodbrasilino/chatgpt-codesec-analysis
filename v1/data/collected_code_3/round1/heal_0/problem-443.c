#include <stdio.h>
#include <limits.h>

int findLargestNegative(int arr[], int n) {
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0 && arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int arr[] = {-1, -3, -5, -7, -9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = findLargestNegative(arr, n);
    if (max == INT_MIN) {
        printf("No negative numbers in the array\n");
    } else {
        printf("Largest negative number in the array is %d\n", max);
    }
    return 0;
}