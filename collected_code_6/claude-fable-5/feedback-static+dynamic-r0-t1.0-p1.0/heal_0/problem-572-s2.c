#include <stdio.h>
#include <stdlib.h>

size_t remove_duplicates(int *arr, size_t size)
{
    size_t i;
    size_t j;
    size_t k;
    size_t new_size;

    if (arr == NULL || size == 0)
    {
        return 0;
    }

    new_size = size;
    i = 0;
    while (i < new_size)
    {
        j = i + 1;
        while (j < new_size)
        {
            if (arr[i] == arr[j])
            {
                for (k = j; k + 1 < new_size; k++)
                {
                    arr[k] = arr[k + 1];
                }
                new_size--;
            }
            else
            {
                j++;
            }
        }
        i++;
    }
    return new_size;
}

int process_lists(size_t num_lists)
{
    size_t list_index;
    size_t list_size;
    size_t new_size;
    size_t i;
    int *list;
    unsigned long input_size;

    for (list_index = 0; list_index < num_lists; list_index++)
    {
        printf("Enter size of list %zu: ", list_index + 1);
        if (scanf("%lu", &input_size) != 1)
        {
            fprintf(stderr, "Invalid size input\n");
            return -1;
        }
        if (input_size == 0 || input_size > 10000)
        {
            fprintf(stderr, "Size out of range\n");
            return -1;
        }
        list_size = (size_t)input_size;

        list = malloc(list_size * sizeof(int));
        if (list == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return -1;
        }

        printf("Enter %zu integers: ", list_size);
        for (i = 0; i < list_size; i++)
        {
            if (scanf("%d", &list[i]) != 1)
            {
                fprintf(stderr, "Invalid integer input\n");
                free(list);
                return -1;
            }
        }

        new_size = remove_duplicates(list, list_size);

        printf("List %zu without duplicates: ", list_index + 1);
        for (i = 0; i < new_size; i++)
        {
            printf("%d ", list[i]);
        }
        printf("\n");

        free(list);
        list = NULL;
    }
    return 0;
}

int main(void)
{
    unsigned long num_lists;

    printf("Enter number of lists: ");
    if (scanf("%lu", &num_lists) != 1)
    {
        fprintf(stderr, "Invalid input for number of lists\n");
        return EXIT_FAILURE;
    }
    if (num_lists == 0 || num_lists > 100)
    {
        fprintf(stderr, "Number of lists out of range\n");
        return EXIT_FAILURE;
    }

    if (process_lists((size_t)num_lists) != 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}