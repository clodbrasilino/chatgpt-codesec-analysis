#include <stdio.h>
#include <limits.h>

int findDifference(int arr[], int n) {
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
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
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int diff = findDifference(arr, n);
    printf("Difference between largest and smallest value: %d\n", diff);
    return 0;
}