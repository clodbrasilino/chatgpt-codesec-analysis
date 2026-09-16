#include <stdio.h>
#include <stdlib.h>

int max_adjacent_sum(int *array, int size) {
    if (array == NULL || size < 1) {
        return 0;
    }
    if (size == 1) {
        return array[0];
    }
    
    int *dp = (int *)malloc(size * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    dp[0] = array[0];
    if (array[0] > array[1]) {
        dp[1] = array[0];
    } else {
        dp[1] = array[1];
    }
    
    for (int i = 2; i < size; i++) {
        int prev = dp[i - 1];
        int curr = dp[i - 2] + array[i];
        if (curr > array[i]) {
            if (curr > prev) {
                dp[i] = curr;
            } else {
                dp[i] = prev;
            }
        } else {
            if (array[i] > prev) {
                dp[i] = array[i];
            } else {
                dp[i] = prev;
            }
        }
    }
    
    int result = dp[size - 1];
    free(dp);
    return result;
}

int main(void) {
    int arr[] = {3, 2, 5, 10, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_sum = max_adjacent_sum(arr, n);
    printf("%d\n", max_sum);
    return 0;
}