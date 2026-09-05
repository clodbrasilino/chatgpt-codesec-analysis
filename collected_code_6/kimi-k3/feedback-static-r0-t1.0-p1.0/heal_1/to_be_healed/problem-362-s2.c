#include <stdio.h>
#include <stdlib.h>

int find_max_occurrence(const int *arr, size_t size, int *max_item, size_t *max_count)
{
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'current_count' can be reduced. [variableScope]
     */
    size_t current_count;
    size_t highest_count;
    int current_item;

    if (arr == NULL || max_item == NULL || max_count == NULL || size == 0)
    {
        return -1;
    }

    highest_count = 0;
    current_item = arr[0];

    for (i = 0; i < size; i++)
    {
        current_count = 0;
        for (j = 0; j < size; j++)
        {
            if (arr[i] == arr[j])
            {
                current_count++;
            }
        }
        if (current_count > highest_count)
        {
            highest_count = current_count;
            current_item = arr[i];
        }
    }

    *max_item = current_item;
    *max_count = highest_count;

    return 0;
}

int main(void)
{
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 1, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int max_item;
    size_t max_count;

    if (find_max_occurrence(arr, size, &max_item, &max_count) == 0)
    {
        printf("Item with maximum occurrences: %d\n", max_item);
        printf("Number of occurrences: %zu\n", max_count);
    }
    else
    {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}