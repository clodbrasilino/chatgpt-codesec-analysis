#include <stdio.h>
#include <limits.h>

int kadane(const int arr[], int n) {
    int maxSoFar = INT_MIN, maxEndingHere = 0;
    for (int i = 0; i < n; i++) {
        maxEndingHere += arr[i];
        if (maxSoFar < maxEndingHere)
            maxSoFar = maxEndingHere;
        if (maxEndingHere < 0)
            maxEndingHere = 0;
    }
    return maxSoFar;
}

int sumArray(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

int findMaxSubarraySumRepeated(const int arr[], int n, int k) {
    int max_kadane = kadane(arr, n);
    int max_prefix_sum = 0, prefix_sum = 0, suffix_sum = 0;

    for (int i = 0; i < n; i++) {
        prefix_sum += arr[i];
        max_prefix_sum = (max_prefix_sum > prefix_sum) ? max_prefix_sum : prefix_sum;
    }

    for (int i = n - 1, sum = 0; i >= 0; --i) {
        sum += arr[i];
        suffix_sum = (sum > suffix_sum) ? sum : suffix_sum;
    }

    int total_sum = sumArray(arr, n);
    int max_sum = 0;

    if (total_sum > 0) {
        max_sum = max_kadane + ((k - 2) * total_sum) + max_prefix_sum + suffix_sum;
    } else {
        max_sum = max_kadane;
    }

    return max_sum;
}

int main() {
    int arr[] = {1, -2, 1, 2, -1};
    int n = 5;
    int k = 3;
    printf("Maximum contiguous sum is %d\n", findMaxSubarraySumRepeated(arr, n, k));
    return 0;
}