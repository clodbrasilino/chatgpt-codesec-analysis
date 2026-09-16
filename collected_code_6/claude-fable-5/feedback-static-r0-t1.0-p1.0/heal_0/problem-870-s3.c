#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long sum_positive(const int *numbers, size_t count)
{
    long sum = 0;

    if (numbers == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; i++) {
        if (numbers[i] > 0) {
            if (sum > LONG_MAX - numbers[i]) {
                fprintf(stderr, "Overflow detected, aborting sum.\n");
                exit(EXIT_FAILURE);
            }
            sum += numbers[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = { 3, -1, 7, 0, -5, 12, 8, -9 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long result;

    result = sum_positive(numbers, count);

    if (printf("Sum of positive numbers: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}