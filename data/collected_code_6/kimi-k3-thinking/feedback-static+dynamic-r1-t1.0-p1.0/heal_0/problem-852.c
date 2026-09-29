#include <stdio.h>
#include <stdlib.h>

size_t remove_negatives(int *arr, size_t size)
{
    size_t i;
    size_t write_index;

    if (arr == NULL)
    {
        return 0;
    }

    write_index = 0;
    for (i = 0; i < size; i++)
    {
        if (arr[i] >= 0)
        {
            arr[write_index] = arr[i];
            write_index++;
        }
    }

    return write_index;
}

int main(void)
{
    int *numbers;
    size_t size;
    size_t new_size;
    size_t i;

    size = 10;
    numbers = (int *)malloc(size * sizeof(int));
    if (numbers == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    numbers[0] = 5;
    numbers[1] = -3;
    numbers[2] = 8;
    numbers[3] = -1;
    numbers[4] = 0;
    numbers[5] = -7;
    numbers[6] = 12;
    numbers[7] = -4;
    numbers[8] = 9;
    numbers[9] = -2;

    printf("Original list: ");
    for (i = 0; i < size; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    new_size = remove_negatives(numbers, size);

    printf("List after removing negatives: ");
    for (i = 0; i < new_size; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("New size: %zu\n", new_size);

    free(numbers);
    numbers = NULL;

    return EXIT_SUCCESS;
}