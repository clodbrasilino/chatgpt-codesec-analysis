#include <stdio.h>
#include <stddef.h>

int sum_negative_numbers(const int numbers[], size_t count)
{
    int sum = 0;
    size_t i;

    if (numbers == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = { 10, -5, 3, -2, 7, -8 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result = sum_negative_numbers(numbers, count);

    printf("Sum of negative numbers: %d\n", result);

    return 0;
}