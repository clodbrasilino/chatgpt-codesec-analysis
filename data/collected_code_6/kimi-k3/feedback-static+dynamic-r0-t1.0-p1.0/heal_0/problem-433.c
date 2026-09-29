#include <stdio.h>
#include <stdlib.h>

int is_greater_than_all(int number, const int *array, size_t size)
{
    size_t i;

    if (array == NULL)
    {
        return 0;
    }

    for (i = 0; i < size; i++)
    {
        if (number <= array[i])
        {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int number;
    int result;
    size_t size;
    size_t i;
    int *array;

    if (printf("Enter the number: ") < 0)
    {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &number) != 1)
    {
        fprintf(stderr, "Invalid input for number\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter the array size: ") < 0)
    {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &size) != 1 || size == 0)
    {
        fprintf(stderr, "Invalid input for array size\n");
        return EXIT_FAILURE;
    }

    array = (int *)malloc(size * sizeof(*array));
    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++)
    {
        if (printf("Enter element %zu: ", i + 1) < 0)
        {
            free(array);
            return EXIT_FAILURE;
        }

        if (scanf("%d", &array[i]) != 1)
        {
            fprintf(stderr, "Invalid input for array element\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    result = is_greater_than_all(number, array, size);

    if (result)
    {
        if (printf("The number is greater than all elements of the array\n") < 0)
        {
            free(array);
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (printf("The number is not greater than all elements of the array\n") < 0)
        {
            free(array);
            return EXIT_FAILURE;
        }
    }

    free(array);
    return EXIT_SUCCESS;
}