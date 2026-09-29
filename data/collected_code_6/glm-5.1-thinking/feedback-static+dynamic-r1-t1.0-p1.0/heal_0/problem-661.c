#include <stdio.h>
#include <stdlib.h>

long long max_ll(long long a, long long b) {
    return a > b ? a : b;
}

long long max3_ll(long long a, long long b, long long c) {
    long long m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    return m;
}

long long max_sum_no_three_consecutive(int arr[], int n) {
    if (n <= 0) return 0;

    long long *dp = malloc(n * sizeof(long long));
    if (!dp) return 0;

    dp[0] = (long long)arr[0];
    if (n == 1) {
        long long r = dp[0];
        free(dp);
        return r;
    }

    dp[1] = max3_ll((long long)arr[0], (long long)arr[1], (long long)arr[0] + arr[1]);
    if (n == 2) {
        long long r = dp[1];
        free(dp);
        return r;
    }

    long long take_one = (long long)arr[2] + max_ll(0, dp[0]);
    long long take_two = (long long)arr[2] + (long long)arr[1];
    dp[2] = max3_ll(dp[1], take_one, take_two);
    if (n == 3) {
        long long r = dp[2];
        free(dp);
        return r;
    }

    for (int i = 3; i < n; i++) {
        take_one = (long long)arr[i] + max_ll(0, dp[i - 2]);
        take_two = (long long)arr[i] + (long long)arr[i - 1] + max_ll(0, dp[i - 3]);
        dp[i] = max3_ll(dp[i - 1], take_one, take_two);
    }

    long long r = dp[n - 1];
    free(dp);
    return r;
}

int main() {
    int arr1[] = {5, 5, 10, 100, 10, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%lld\n", max_sum_no_three_consecutive(arr1, n1));

    int arr2[] = {1, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%lld\n", max_sum_no_three_consecutive(arr2, n2));

    int arr3[] = {-1, -2, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%lld\n", max_sum_no_three_consecutive(arr3, n3));

    int arr4[] = {100, 1000, 100, 100, 1000, 100};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%lld\n", max_sum_no_three_consecutive(arr4, n4));

    return 0;
}