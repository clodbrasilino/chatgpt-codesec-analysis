#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_even_at_even_positions(const int *arr, size_t n)
{
    long long sum = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < n; i += 2) {
        if (arr[i] % 2 == 0) {
            sum += (long long)arr[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = {2, 5, 4, 7, 6, 9, 8, 11, 10};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result;

    result = sum_even_at_even_positions(numbers, count);

    if (printf("Sum of even numbers at even positions: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}