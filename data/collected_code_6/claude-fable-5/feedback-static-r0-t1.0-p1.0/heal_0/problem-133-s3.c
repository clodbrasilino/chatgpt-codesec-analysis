#include <stdio.h>
#include <stddef.h>

long long sum_negatives(const int *numbers, size_t count)
{
    long long sum = 0;
    size_t i;

    if (numbers == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (numbers[i] < 0) {
            sum += (long long)numbers[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = { 3, -5, 7, -2, 0, -8, 10 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result;

    result = sum_negatives(numbers, count);

    if (printf("Sum of negative numbers: %lld\n", result) < 0) {
        return 1;
    }

    return 0;
}