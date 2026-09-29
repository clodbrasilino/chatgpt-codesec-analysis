#include <stdio.h>
#include <stdlib.h>

size_t remove_even_numbers(const int *input, size_t size, int **output)
{
    size_t i;
    size_t count;
    int *result;

    if (output == NULL)
    {
        return 0;
    }
    *output = NULL;

    if (input == NULL || size == 0)
    {
        return 0;
    }

    count = 0;
    for (i = 0; i < size; i++)
    {
        if (input[i] % 2 != 0)
        {
            count++;
        }
    }

    if (count == 0)
    {
        return 0;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL)
    {
        return 0;
    }

    count = 0;
    for (i = 0; i < size; i++)
    {
        if (input[i] % 2 != 0)
        {
            result[count] = input[i];
            count++;
        }
    }

    *output = result;
    return count;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int *odd_numbers = NULL;
    size_t odd_count;
    size_t i;

    odd_count = remove_even_numbers(numbers, size, &odd_numbers);

    printf("Original list: ");
    for (i = 0; i < size; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("List after removing even numbers: ");
    for (i = 0; i < odd_count; i++)
    {
        printf("%d ", odd_numbers[i]);
    }
    printf("\n");

    free(odd_numbers);
    odd_numbers = NULL;

    return EXIT_SUCCESS;
}