#include <stdio.h>
#include <limits.h>

int findSum(int arr[], int n) {
    int max = INT_MIN;
    int min = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }

    return max + min;
}

int main() {
    int arr[] = {12, 3, 5, 15, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = findSum(arr, n);

    printf("Sum of largest and smallest value is %d", sum);
    return 0;
}