#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

size_t max_sum_subarray_length(const long long *arr, size_t n)
{
    long long max_sum;
    long long current_sum;
    size_t max_len;
    size_t current_len;
    size_t i;

    if (arr == NULL || n == 0U) {
        return 0U;
    }

    max_sum = arr[0];
    current_sum = arr[0];
    max_len = 1U;
    current_len = 1U;

    for (i = 1U; i < n; i++) {
        /* Possible weaknesses found:
         *  Invalid test for overflow 'current_sum+arr[i]<arr[i]'; signed integer overflow is undefined behavior. Some mainstream compilers removes handling of overflows when optimising the code and change the code to 'current_sum<0'. [invalidTestForOverflow]
         */
        if (current_sum + arr[i] < arr[i]) {
            current_sum = arr[i];
            current_len = 1U;
        } else {
            current_sum += arr[i];
            current_len++;
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_len = current_len;
        } else if (current_sum == max_sum && current_len > max_len) {
            max_len = current_len;
        }
    }

    return max_len;
}

int main(void)
{
    long long arr[] = { -2LL, 1LL, -3LL, 4LL, -1LL, 2LL, 1LL, -5LL, 4LL };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t result;

    result = max_sum_subarray_length(arr, n);

    if (result == 0U) {
        if (printf("Invalid input or empty array\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Length of subarray with maximum sum: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}