#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int minDifference(int arr[], int n) {
    if (n < 2) {
        return -1;
    }
    qsort(arr, n, sizeof(int), compare);
    int min_diff = abs(arr[1] - arr[0]);
    for (int i = 2; i < n; i++) {
        int diff = abs(arr[i] - arr[i - 1]);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }
    return min_diff;
}

int main() {
    int arr[] = {10, 8, 3, 7, 5, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = minDifference(arr, n);
    if (result == -1) {
        printf("Array must have at least two elements.\n");
    } else {
        printf("Minimum difference: %d\n", result);
    }
    return 0;
}