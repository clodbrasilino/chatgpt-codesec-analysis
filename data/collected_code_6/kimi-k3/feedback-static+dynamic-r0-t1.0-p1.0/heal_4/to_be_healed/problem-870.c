#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 522, got <no output>
  *  test case 0 failed: expected 48, got <no output>
  *  test case 1 failed: expected 50, got <no output>
  */

int sum_positive_numbers(const int *numbers, size_t count)
{
    int sum = 0;
    size_t i;

    if (numbers == NULL)
    {
        return 0;
    }

    for (i = 0; i < count; i++)
    {
        if (numbers[i] > 0)
        {
            sum += numbers[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = {1, -2, 4, -1, 7, 0, -3, 2, 8, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result;

    result = sum_positive_numbers(numbers, count);
    printf("%d\n", result);

    return 0;
}