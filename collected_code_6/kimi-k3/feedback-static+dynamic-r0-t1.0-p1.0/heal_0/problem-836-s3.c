#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_sum_subarray_length(const int *arr, size_t n)
{
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long max_sum = LLONG_MIN;
    long long current_sum = 0;
    size_t max_length = 0;
    size_t current_length = 0;

    for (size_t i = 0; i < n; i++) {
        current_sum += arr[i];
        current_length++;

        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_length = current_length;
        }

        if (current_sum < 0) {
            current_sum = 0;
            current_length = 0;
        }
    }

    return (int)max_length;
}

int main(void)
{
    int arr[] = {1, -2, 3, 4, -1, 2, 1, -5, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int length = max_sum_subarray_length(arr, n);
    printf("%d\n", length);

    return 0;
}