#include <stdio.h>
#include <stdlib.h>

double calculate_average(const int *list, size_t length)
{
    double sum = 0.0;
    size_t i;

    if (list == NULL || length == 0) {
        return 0.0;
    }

    for (i = 0; i < length; i++) {
        sum += list[i];
    }

    return sum / length;
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    double average;

    average = calculate_average(numbers, length);
    printf("Average: %.2f\n", average);

    return 0;
}