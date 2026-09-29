#include <stdio.h>
#include <stdlib.h>

long long sum_even_at_even_positions(const int *arr, size_t size)
{
    long long sum = 0;
    size_t i;

    if (arr == NULL || size == 0)
    {
        return 0;
    }

    for (i = 0; i < size; i += 2)
    {
        if (arr[i] % 2 == 0)
        {
            sum += arr[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = {4, 7, 6, 3, 8, 10, 12, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result;

    result = sum_even_at_even_positions(numbers, count);

    if (printf("Sum of even numbers at even positions: %lld\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}