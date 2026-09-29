#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int number)
{
    int sum = 0;
    unsigned int value;

    if (number < 0) {
        value = (unsigned int)(-(long)number);
    } else {
        value = (unsigned int)number;
    }

    while (value > 0U) {
        sum += (int)(value % 10U);
        value /= 10U;
    }

    return sum;
}

int main(void)
{
    int numbers[] = { 123, 456, 789, 0, -45, 9999 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        int result = sum_of_digits(numbers[i]);
        if (printf("Sum of digits of %d is %d\n", numbers[i], result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}