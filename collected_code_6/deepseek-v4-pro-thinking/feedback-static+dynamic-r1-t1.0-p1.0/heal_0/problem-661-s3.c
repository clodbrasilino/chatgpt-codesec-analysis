#include <stddef.h>
#include <stdio.h>

long long maxSumNoThreeConsecutive(const int arr[], size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long dp_prev1 = 0;
    long long dp_prev2 = 0;
    long long dp_prev3 = 0;
    int prev_element = 0;

    for (size_t i = 0; i < n; ++i) {
        long long current = dp_prev1;

        long long include_current = (long long)arr[i] + dp_prev2;
        if (include_current > current) {
            current = include_current;
        }

        long long include_current_and_prev = (long long)arr[i] + (long long)prev_element + dp_prev3;
        if (include_current_and_prev > current) {
            current = include_current_and_prev;
        }

        dp_prev3 = dp_prev2;
        dp_prev2 = dp_prev1;
        dp_prev1 = current;
        prev_element = arr[i];
    }

    return dp_prev1;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result = maxSumNoThreeConsecutive(arr, n);
    printf("%lld\n", result);
    return 0;
}