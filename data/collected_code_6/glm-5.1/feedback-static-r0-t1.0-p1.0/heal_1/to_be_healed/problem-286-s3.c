#include <stdio.h>
#include <stdlib.h>

long long max(long long a, long long b) {
    return a > b ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long maxSubArraySum(long long* arr, int n) {
    long long max_so_far = arr[0];
    long long curr_max = arr[0];

    for (int i = 1; i < n; i++) {
        curr_max = max(arr[i], curr_max + arr[i]);
        max_so_far = max(max_so_far, curr_max);
    }

    return max_so_far;
}

long long maxSubArraySumKTimes(int* arr, int n, int k) {
    if (n == 0) {
        return 0;
    }

    long long* doubleArr = (long long*)malloc(2 * n * sizeof(long long));
    if (doubleArr == NULL) {
        exit(1);
    }

    for (int i = 0; i < 2 * n; i++) {
        doubleArr[i] = (long long)arr[i % n];
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    if (k == 1) {
        long long res = maxSubArraySum(doubleArr, n);
        free(doubleArr);
        return res;
    }

    long long twoSum = maxSubArraySum(doubleArr, 2 * n);
    free(doubleArr);

    if (sum <= 0) {
        return twoSum;
    }

    return twoSum + (long long)(k - 2) * sum;
}

int main() {
    int arr[] = {1, -2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;

    long long result = maxSubArraySumKTimes(arr, n, k);
    printf("%lld\n", result);

    return 0;
}