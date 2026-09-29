#include <stdio.h>
#include <stdlib.h>

int *find_odd_numbers(const int *numbers, size_t count, size_t *odd_count)
{
    size_t i;
    size_t j;
    size_t valid_odd_count;
    int *odd_numbers;

    if (numbers == NULL || odd_count == NULL)
    {
        return NULL;
    }

    valid_odd_count = 0;

    for (i = 0; i < count; i++)
    {
        if (numbers[i] % 2 != 0)
        {
            valid_odd_count++;
        }
    }

    if (valid_odd_count == 0)
    {
        *odd_count = 0;
        return NULL;
    }

    odd_numbers = malloc(valid_odd_count * sizeof(int));

    if (odd_numbers == NULL)
    {
        return NULL;
    }

    j = 0;

    for (i = 0; i < count; i++)
    {
        if (numbers[i] % 2 != 0)
        {
            odd_numbers[j] = numbers[i];
            j++;
        }
    }

    *odd_count = valid_odd_count;

    return odd_numbers;
}

int main(void)
{
    int numbers[] = {12, 7, 9, 20, 33, 42, 55, 68, 71, 90};
    size_t count;
    size_t odd_count;
    size_t i;
    int *odd_numbers;

    count = sizeof(numbers) / sizeof(numbers[0]);
    odd_count = 0;

    odd_numbers = find_odd_numbers(numbers, count, &odd_count);

    if (odd_count == 0 && odd_numbers == NULL)
    {
        printf("No odd numbers found.\n");
        return 0;
    }

    if (odd_numbers == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Odd numbers: ");

    for (i = 0; i < odd_count; i++)
    {
        printf("%d ", odd_numbers[i]);
    }

    printf("\n");

    free(odd_numbers);

    return 0;
}