#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long array_sum(const int *arr, size_t length, int *status)
{
    long long sum = 0;

    if (arr == NULL || status == NULL) {
        if (status != NULL) {
            *status = -1;
        }
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        if ((arr[i] > 0 && sum > LLONG_MAX - arr[i]) ||
            (arr[i] < 0 && sum < LLONG_MIN - arr[i])) {
            *status = -1;
            return 0;
        }
        sum += arr[i];
    }

    *status = 0;
    return sum;
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int status = 0;

    long long result = array_sum(numbers, count, &status);

    if (status != 0) {
        fprintf(stderr, "Error computing array sum\n");
        return EXIT_FAILURE;
    }

    printf("Sum of array: %lld\n", result);

    return EXIT_SUCCESS;
}