#include <stdio.h>
#include <stdlib.h>

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long kadane(const long long *arr, long long n) {
    long long max_current = arr[0];
    long long max_global = arr[0];
    for (long long i = 1; i < n; i++) {
        max_current = max(arr[i], max_current + arr[i]);
        if (max_current > max_global) {
            max_global = max_current;
        }
    }
    return max_global;
}

long long max_contiguous_sum(const long long *arr, long long n, long long k) {
    if (n == 0 || k == 0) {
        return 0;
    }

    long long total_sum = 0;
    for (long long i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    if (k == 1) {
        return kadane(arr, n);
    }

    long long *temp = (long long *)malloc(2 * n * sizeof(long long));
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }

    for (long long i = 0; i < 2 * n; i++) {
        temp[i] = arr[i % n];
    }

    if (total_sum <= 0) {
        long long res = kadane(temp, 2 * n);
        free(temp);
        return res;
    } else {
        long long res = kadane(temp, 2 * n) + (k - 2) * total_sum;
        free(temp);
        return res;
    }
}

int main() {
    long long arr[] = {1, -2, 1};
    long long n = sizeof(arr) / sizeof(arr[0]);
    long long k = 5;

    long long result = max_contiguous_sum(arr, n, k);
    printf("%lld\n", result);

    return 0;
}