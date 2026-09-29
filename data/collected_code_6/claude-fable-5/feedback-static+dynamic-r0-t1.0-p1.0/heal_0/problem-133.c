#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long sum_of_negatives(const int *numbers, size_t count)
{
    long sum = 0;
    size_t i;

    if (numbers == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (numbers[i] < 0) {
            sum += (long)numbers[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = { 4, -3, 7, -8, 12, -1, 0, -5 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long result;

    result = sum_of_negatives(numbers, count);

    if (printf("Sum of negative numbers: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}