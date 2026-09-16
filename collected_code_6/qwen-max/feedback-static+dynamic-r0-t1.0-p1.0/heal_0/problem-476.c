#include <stdio.h>
#include <limits.h>

int findSumOfExtremes(int *arr, int n) {
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
    return min + max;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = findSumOfExtremes(arr, n);
    printf("Sum of the largest and smallest value: %d\n", sum);
    return 0;
}