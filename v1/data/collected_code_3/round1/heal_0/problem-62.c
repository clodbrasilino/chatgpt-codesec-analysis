#include <stdio.h>
#include <limits.h>

int findSmallest(int arr[], int n) {
    int i, min = INT_MAX;
    for (i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    int arr[] = {12, 23, 4, 56, 78, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Smallest number in the array is %d", findSmallest(arr, n));
    return 0;
}