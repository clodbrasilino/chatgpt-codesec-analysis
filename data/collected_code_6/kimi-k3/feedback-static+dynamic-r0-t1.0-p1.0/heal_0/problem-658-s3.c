#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_max_occurrence(const int *arr, size_t size, int *result)
{
    if (arr == NULL || result == NULL || size == 0)
    {
        return -1;
    }

    int max_item = arr[0];
    size_t max_count = 1;

    for (size_t i = 0; i < size; i++)
    {
        size_t current_count = 1;

        for (size_t j = i + 1; j < size; j++)
        {
            if (arr[i] == arr[j])
            {
                current_count++;
            }
        }

        if (current_count > max_count)
        {
            max_count = current_count;
            max_item = arr[i];
        }
    }

    *result = max_item;
    return 0;
}

int main(void)
{
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 2, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = 0;

    if (find_max_occurrence(arr, size, &result) == 0)
    {
        printf("Item with maximum occurrences: %d\n", result);
    }
    else
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}