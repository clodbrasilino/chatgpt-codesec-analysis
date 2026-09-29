#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_positive(const int *numbers, size_t count)
{
    int sum = 0;

    if (numbers == NULL)
    {
        return 0;
    }

    for (size_t i = 0; i < count; i++)
    {
        if (numbers[i] > 0)
        {
            if (sum > INT_MAX - numbers[i])
            {
                exit(EXIT_FAILURE);
            }
            sum += numbers[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = {1, -2, 3, -4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    int result = sum_positive(numbers, count);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}