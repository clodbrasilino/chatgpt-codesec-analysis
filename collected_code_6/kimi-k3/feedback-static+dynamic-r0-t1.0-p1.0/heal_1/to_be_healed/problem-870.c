#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 522, got <no output>
  *  test case 0 failed: expected 48, got <no output>
  *  test case 1 failed: expected 50, got <no output>
  */

double sum_positive_numbers(const double *numbers, size_t count)
{
    double sum = 0.0;
    size_t i;

    if (numbers == NULL)
    {
        return 0.0;
    }

    for (i = 0; i < count; i++)
    {
        if (numbers[i] > 0.0)
        {
            sum += numbers[i];
        }
    }

    return sum;
}

int main(void)
{
    double numbers[] = {1.5, -2.3, 4.0, -1.0, 7.2, 0.0, -3.5, 2.8};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    double result;

    result = sum_positive_numbers(numbers, count);
    printf("Sum of positive numbers: %.2f\n", result);

    return 0;
}