#include <stdio.h>
#include <stdlib.h>

int max3Num(int a, int b, int c) {
    if (a > b) {
        if (a > c) {
            return a;
        } else {
            return c;
        }
    }
    
    if (b > c) {
        return b;
    } else {
        return c;
    }
}

int maxNonConsecutiveSum(int arr[], int n) {
    if (n == 0) return 0;
    
    int sum[n];
    sum[0] = arr[0];
    sum[1] = arr[0] + arr[1];
    sum[2] = max3Num(sum[1], sum[0] + arr[2], arr[1] + arr[2]);

    for (int i = 3; i < n; i++) {
        sum[i] = max3Num(
            sum[i-1],
            sum[i-2] + arr[i],
            sum[i-3] + arr[i-1] + arr[i]
        );
    }
    return sum[n-1];
}

int main() {
    int arr[] = { 1, 2, 9, 4, 5, 0, 4, 11, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int maxSum = maxNonConsecutiveSum(arr, n);
    printf("Maximum sum with no three consecutive elements present is: %d\n", maxSum);

    return 0;
}