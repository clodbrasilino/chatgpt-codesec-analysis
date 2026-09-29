#include <stdio.h>

double average(const int *numbers, size_t length)
{
    double sum;
    size_t i;

    if (numbers == NULL || length == 0)
    {
        return 0.0;
    }

    sum = 0.0;
    for (i = 0; i < length; i++)
    {
        sum += numbers[i];
    }

    return sum / (double)length;
}

int main(void)
{
    int values[] = {10, 20, 30, 40, 50};
    size_t length;
    double result;

    length = sizeof(values) / sizeof(values[0]);
    result = average(values, length);

    if (printf("Average: %.2f\n", result) < 0)
    {
        return 1;
    }

    return 0;
}