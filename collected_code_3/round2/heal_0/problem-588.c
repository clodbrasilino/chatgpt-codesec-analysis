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
    int arr[] = {2, 3, 1, 6, 10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int diff = findDifference(arr, n);
    printf("The difference between largest and smallest value in the array is %d", diff);
    return 0;
}