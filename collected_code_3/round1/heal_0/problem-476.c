#include <stdio.h>
#include <limits.h>

int findSum(int arr[], int n) {
    int max_val = INT_MIN;
    int min_val = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val)
            max_val = arr[i];
        if (arr[i] < min_val)
            min_val = arr[i];
    }

    return max_val + min_val;
}

int main() {
    int arr[] = {10, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Sum of largest and smallest value in the array is %d", findSum(arr, n));
    return 0;
}