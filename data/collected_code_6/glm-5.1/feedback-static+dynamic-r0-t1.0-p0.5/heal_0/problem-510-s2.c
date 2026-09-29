#include <stdio.h>
#include <stdlib.h>

int count_subsequences(int arr[], int n, int k) {
    if (k <= 1) {
        return 0;
    }
    int result = 0;
    long long product = 1;
    int left = 0;
    for (int right = 0; right < n; right++) {
        product *= arr[right];
        while (product >= k && left <= right) {
            product /= arr[left];
            left++;
        }
        result += right - left + 1;
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 10;
    int count = count_subsequences(arr, n, k);
    printf("%d\n", count);
    return 0;
}