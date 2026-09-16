#include <stdio.h>
#include <stdlib.h>

size_t remove_odd_numbers(int *numbers, size_t size)
{
    size_t read_index;
    size_t write_index;

    if (numbers == NULL)
    {
        return 0;
    }

    write_index = 0;
    for (read_index = 0; read_index < size; read_index++)
    {
        if (numbers[read_index] % 2 == 0)
        {
            numbers[write_index] = numbers[read_index];
            write_index++;
        }
    }
    return write_index;
}

int main(void)
{
    int *numbers;
    size_t count;
    size_t new_count;
    size_t i;
    long input_value;

    printf("Enter the number of elements: ");
    if (scanf("%ld", &input_value) != 1 || input_value <= 0)
    {
        fprintf(stderr, "Invalid number of elements.\n");
        return EXIT_FAILURE;
    }

    count = (size_t)input_value;

    numbers = (int *)malloc(count * sizeof(int));
    if (numbers == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu integers:\n", count);
    for (i = 0; i < count; i++)
    {
        if (scanf("%d", &numbers[i]) != 1)
        {
            fprintf(stderr, "Invalid input.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    new_count = remove_odd_numbers(numbers, count);

    if (new_count == 0)
    {
        printf("No even numbers remain.\n");
    }
    else
    {
        printf("List after removing odd numbers:\n");
        for (i = 0; i < new_count; i++)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    free(numbers);

    return EXIT_SUCCESS;
}