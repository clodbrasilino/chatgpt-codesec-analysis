#include <stdio.h>
#include <limits.h>

int findMaxInSortedRotatedArray(const int arr[], int n) {
    int max = INT_MIN, i;
    for (i = 0; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    const int arr[] = {5, 6, 7, 8, 9, 10, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max = findMaxInSortedRotatedArray(arr, n);
    printf("Maximum element is %d\n", max);
    return 0;
}