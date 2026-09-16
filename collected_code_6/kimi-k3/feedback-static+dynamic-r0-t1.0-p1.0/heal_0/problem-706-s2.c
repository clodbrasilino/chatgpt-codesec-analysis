#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int is_subset(const int *subset, size_t subset_size, const int *array, size_t array_size)
{
    int *sorted_subset;
    int *sorted_array;
    size_t i;
    size_t j;

    if (subset_size == 0)
    {
        return 1;
    }

    if (array_size == 0 || subset_size > array_size)
    {
        return 0;
    }

    if (subset == NULL || array == NULL)
    {
        return 0;
    }

    sorted_subset = malloc(subset_size * sizeof(int));
    if (sorted_subset == NULL)
    {
        return 0;
    }

    sorted_array = malloc(array_size * sizeof(int));
    if (sorted_array == NULL)
    {
        free(sorted_subset);
        return 0;
    }

    memcpy(sorted_subset, subset, subset_size * sizeof(int));
    memcpy(sorted_array, array, array_size * sizeof(int));

    qsort(sorted_subset, subset_size, sizeof(int), compare_ints);
    qsort(sorted_array, array_size, sizeof(int), compare_ints);

    i = 0;
    j = 0;

    while (i < subset_size && j < array_size)
    {
        if (sorted_subset[i] == sorted_array[j])
        {
            i++;
            j++;
        }
        else if (sorted_subset[i] > sorted_array[j])
        {
            j++;
        }
        else
        {
            free(sorted_subset);
            free(sorted_array);
            return 0;
        }
    }

    free(sorted_subset);
    free(sorted_array);

    return (i == subset_size);
}

int main(void)
{
    int array1[] = {11, 1, 13, 21, 3, 7};
    int subset1[] = {11, 3, 7, 1};
    int array2[] = {1, 2, 3, 4, 5};
    int subset2[] = {1, 6};
    int array3[] = {10, 5, 2, 23, 19};
    int subset3[] = {19, 5, 2};
    int result;

    size_t size_array1 = sizeof(array1) / sizeof(array1[0]);
    size_t size_subset1 = sizeof(subset1) / sizeof(subset1[0]);
    size_t size_array2 = sizeof(array2) / sizeof(array2[0]);
    size_t size_subset2 = sizeof(subset2) / sizeof(subset2[0]);
    size_t size_array3 = sizeof(array3) / sizeof(array3[0]);
    size_t size_subset3 = sizeof(subset3) / sizeof(subset3[0]);

    result = is_subset(subset1, size_subset1, array1, size_array1);
    printf("Test 1: %s\n", result ? "Subset" : "Not a subset");

    result = is_subset(subset2, size_subset2, array2, size_array2);
    printf("Test 2: %s\n", result ? "Subset" : "Not a subset");

    result = is_subset(subset3, size_subset3, array3, size_array3);
    printf("Test 3: %s\n", result ? "Subset" : "Not a subset");

    return 0;
}