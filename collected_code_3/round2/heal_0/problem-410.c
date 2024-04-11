#include <stdio.h>
#include <limits.h>

int findMin(int arr[], int n) {
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    int arr[] = {10, 20, 30, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Minimum value in the array is %d\n", findMin(arr, n));
    return 0;
}