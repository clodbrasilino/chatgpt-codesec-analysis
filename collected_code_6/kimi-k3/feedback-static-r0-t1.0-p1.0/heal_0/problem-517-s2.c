#include <stdio.h>
#include <stdlib.h>

int find_largest_positive(const int *arr, size_t size)
{
    int largest = -1;
    size_t i;

    if (arr == NULL || size == 0)
    {
        return -1;
    }

    for (i = 0; i < size; i++)
    {
        if (arr[i] > 0 && (largest == -1 || arr[i] > largest))
        {
            largest = arr[i];
        }
    }

    return largest;
}

int main(void)
{
    int numbers[] = {3, -5, 12, 7, -2, 9, 0, 15, 4};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int result;

    result = find_largest_positive(numbers, size);

    if (result == -1)
    {
        printf("No positive number found in the list.\n");
    }
    else
    {
        printf("The largest positive number is: %d\n", result);
    }

    return 0;
}