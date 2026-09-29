#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSumWithoutThreeConsecutive(int arr[], int n) {
    if (n == 1)
        return arr[0];
    if (n == 2)
        return max(arr[0], arr[1]);
    if (n == 3)
        return max(max(arr[0], arr[1]), arr[2]);

    int sum[n];

    sum[0] = arr[0];
    sum[1] = arr[1];
    sum[2] = arr[2];

    for (int i = 3; i < n; i++)
        sum[i] = max(max(sum[i-1], sum[i-2] + arr[i]), arr[i] + arr[i-1] + max(0, sum[i-3]));

    return max(sum[n-1], sum[n-2]);
}

int main() {
    int arr[] = {1000, 1000, 1000, 1000, 1000};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d", maxSumWithoutThreeConsecutive(arr, n));
    return 0;
}