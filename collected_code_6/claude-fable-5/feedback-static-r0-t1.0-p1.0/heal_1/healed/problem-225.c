#include <stdio.h>
#include <stdlib.h>

int findMin(const int *arr, size_t n, int *result)
{
    size_t low;
    size_t high;

    if (arr == NULL || n == 0U || result == NULL)
    {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    while (low < high)
    {
        const size_t mid = low + ((high - low) / 2U);
        if (arr[mid] > arr[high])
        {
            low = mid + 1U;
        }
        else
        {
            high = mid;
        }
    }

    *result = arr[low];
    return 0;
}

int main(void)
{
    int arr1[] = {4, 5, 6, 7, 0, 1, 2};
    int arr2[] = {3, 4, 5, 1, 2};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {2};
    int minValue;

    if (findMin(arr1, sizeof(arr1) / sizeof(arr1[0]), &minValue) == 0)
    {
        (void)printf("Minimum of arr1: %d\n", minValue);
    }
    else
    {
        (void)fprintf(stderr, "Error finding minimum in arr1\n");
        return EXIT_FAILURE;
    }

    if (findMin(arr2, sizeof(arr2) / sizeof(arr2[0]), &minValue) == 0)
    {
        (void)printf("Minimum of arr2: %d\n", minValue);
    }
    else
    {
        (void)fprintf(stderr, "Error finding minimum in arr2\n");
        return EXIT_FAILURE;
    }

    if (findMin(arr3, sizeof(arr3) / sizeof(arr3[0]), &minValue) == 0)
    {
        (void)printf("Minimum of arr3: %d\n", minValue);
    }
    else
    {
        (void)fprintf(stderr, "Error finding minimum in arr3\n");
        return EXIT_FAILURE;
    }

    if (findMin(arr4, sizeof(arr4) / sizeof(arr4[0]), &minValue) == 0)
    {
        (void)printf("Minimum of arr4: %d\n", minValue);
    }
    else
    {
        (void)fprintf(stderr, "Error finding minimum in arr4\n");
        return EXIT_FAILURE;
    }

    if (findMin(NULL, 0U, &minValue) != 0)
    {
        (void)printf("Correctly handled invalid input\n");
    }

    return EXIT_SUCCESS;
}