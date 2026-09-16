#include <stdio.h>
#include <limits.h>

int findSumOfExtremes(int arr[], int n) {
    int min = INT_MAX, max = INT_MIN;
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
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findSumOfExtremes(arr, n);
    printf("The sum of the smallest and largest values is: %d\n", result);
    return 0;
}