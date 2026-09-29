#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

int compare_ints(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

bool is_subset(const int *subset, size_t subset_size, const int *array, size_t array_size)
{
    int *sorted_subset = NULL;
    int *sorted_array = NULL;
    size_t i = 0;
    size_t j = 0;
    bool result = false;

    if (subset == NULL || array == NULL)
    {
        return false;
    }

    if (subset_size == 0)
    {
        return true;
    }

    if (array_size == 0 || subset_size > array_size)
    {
        return false;
    }

    if (subset_size > SIZE_MAX / sizeof(int) || array_size > SIZE_MAX / sizeof(int))
    {
        return false;
    }

    sorted_subset = malloc(subset_size * sizeof(int));
    if (sorted_subset == NULL)
    {
        return false;
    }

    sorted_array = malloc(array_size * sizeof(int));
    if (sorted_array == NULL)
    {
        free(sorted_subset);
        return false;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     */
    if (memcpy_s(sorted_subset, subset_size * sizeof(int), subset, subset_size * sizeof(int)) != 0)
    {
        free(sorted_subset);
        free(sorted_array);
        return false;
    }

    if (memcpy_s(sorted_array, array_size * sizeof(int), array, array_size * sizeof(int)) != 0)
    {
        free(sorted_subset);
        free(sorted_array);
        return false;
    }

    qsort(sorted_subset, subset_size, sizeof(int), compare_ints);
    qsort(sorted_array, array_size, sizeof(int), compare_ints);

    while (i < subset_size && j < array_size)
    {
        /* Possible weaknesses found:
         *  'memcpy' declared here
         */
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
            goto cleanup;
        }
    }

    result = (i == subset_size);

cleanup:
    free(sorted_subset);
    free(sorted_array);
    return result;
}

int main(void)
{
    int array1[] = {11, 1, 13, 21, 3, 7};
    int subset1[] = {11, 3, 7, 1};
    int array2[] = {1, 2, 3, 4, 5};
    int subset2[] = {1, 6};
    int array3[] = {10, 5, 2, 23, 19};
    int subset3[] = {19, 5, 2};
    bool result;

    size_t size_array1 = sizeof(array1) / sizeof(array1[0]);
    size_t size_subset1 = sizeof(subset1) / sizeof(subset1[0]);
    size_t size_array2 = sizeof(array2) / sizeof(array2[0]);
    size_t size_subset2 = sizeof(subset2) / sizeof(subset2[0]);
    size_t size_array3 = sizeof(array3) / sizeof(array3[0]);
    size_t size_subset3 = sizeof(subset3) / sizeof(subset3[0]);

    result = is_subset(subset1, size_subset1, array1, size_array1);
    printf("Test 1: %s\n", result ? "true" : "false");

    result = is_subset(subset2, size_subset2, array2, size_array2);
    printf("Test 2: %s\n", result ? "true" : "false");

    result = is_subset(subset3, size_subset3, array3, size_array3);
    printf("Test 3: %s\n", result ? "true" : "false");

    return 0;
}