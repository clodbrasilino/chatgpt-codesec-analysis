#include <stdio.h>
#include <stdlib.h>

int countSubsequences(const int *arr, int n, long long k) {
    if (n == 0 || k <= 1)
        return 0;

    int count = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            product *= arr[j];
            if (product < k)
                count++;
            else
                break;
        }
    }
    return count;
}

int main() {
    const int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    long long k = 10;
    int result = countSubsequences(arr, n, k);
    printf("Number of subsequences with product less than %lld: %d\n", k, result);
    return 0;
}