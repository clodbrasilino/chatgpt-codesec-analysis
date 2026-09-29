#include <stdio.h>
#include <stdlib.h>

int find_max_frequency(const int *arr, size_t size, int *max_item, int *max_count)
{
    size_t i;
    size_t j;
    int count;
    int best_item;
    int best_count;

    if (arr == NULL || max_item == NULL || max_count == NULL)
    {
        return -1;
    }

    if (size == 0)
    {
        return -1;
    }

    best_item = arr[0];
    best_count = 0;

    for (i = 0; i < size; i++)
    {
        count = 0;
        for (j = 0; j < size; j++)
        {
            if (arr[j] == arr[i])
            {
                count++;
            }
        }
        if (count > best_count)
        {
            best_count = count;
            best_item = arr[i];
        }
    }

    *max_item = best_item;
    *max_count = best_count;

    return 0;
}

int main(void)
{
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 1, 1, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int max_item = 0;
    int max_count = 0;
    size_t i;

    printf("Array: ");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (find_max_frequency(arr, size, &max_item, &max_count) != 0)
    {
        fprintf(stderr, "Error: failed to find maximum frequency item\n");
        return EXIT_FAILURE;
    }

    printf("Item with maximum frequency: %d (occurs %d times)\n", max_item, max_count);

    return EXIT_SUCCESS;
}