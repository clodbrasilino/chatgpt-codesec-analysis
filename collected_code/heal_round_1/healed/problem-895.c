#include <stdio.h>

int maxSumNoAdjacent(const int arr[], int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return arr[0];
    else if (n == 2)
        return (arr[0] > arr[1]) ? arr[0] : arr[1];
    
    int prev_prev = arr[0];
    int prev = (arr[0] > arr[1]) ? arr[0] : arr[1];
    int curr_max = prev;

    for (int i = 2; i < n; ++i) {
        curr_max = (arr[i] + prev_prev > prev) ? arr[i] + prev_prev : prev;
        prev_prev = prev;
        prev = curr_max;
    }

    return curr_max;
}

int main() {
    int arr[] = {5, 1, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int maxSum = maxSumNoAdjacent(arr, n);
    
    printf("Maximum sum of non-adjacent elements: %d\n", maxSum);
    
    return 0;
}