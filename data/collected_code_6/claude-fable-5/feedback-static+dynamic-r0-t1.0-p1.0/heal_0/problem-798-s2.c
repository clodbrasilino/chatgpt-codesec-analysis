#include <stdio.h>
#include <stddef.h>

long long array_sum(const int *arr, size_t len)
{
    long long sum = 0;

    if (arr == NULL) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        sum += arr[i];
    }

    return sum;
}

int main(void)
{
    int numbers[] = {3, 7, 1, 9, 4, 6};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result;

    result = array_sum(numbers, count);

    if (printf("Sum of array: %lld\n", result) < 0) {
        return 1;
    }

    return 0;
}