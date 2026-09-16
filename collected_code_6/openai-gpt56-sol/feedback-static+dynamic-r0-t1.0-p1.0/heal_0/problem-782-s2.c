#include <stdio.h>
#include <stdlib.h>

static int sum_odd_length_subarrays(const int *array, size_t length, long long *result)
{
    if (array == NULL || result == NULL) {
        return -1;
    }

    long long sum = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t total_subarrays = (i + 1U) * (length - i);
        size_t odd_subarrays = (total_subarrays + 1U) / 2U;
        sum += (long long)array[i] * (long long)odd_subarrays;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    int array[] = {1, 4, 2, 5, 3};
    size_t length = sizeof(array) / sizeof(array[0]);
    long long result = 0;

    if (sum_odd_length_subarrays(array, length, &result) != 0) {
        fputs("Failed to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}