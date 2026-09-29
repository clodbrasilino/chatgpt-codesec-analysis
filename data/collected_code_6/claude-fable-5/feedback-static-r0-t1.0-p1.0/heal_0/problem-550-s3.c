#include <stdio.h>
#include <stdlib.h>

int findMax(const int *arr, size_t n, int *result);

int findMax(const int *arr, size_t n, int *result)
{
    size_t low;
    size_t high;
    size_t mid;

    if ((arr == NULL) || (n == 0U) || (result == NULL))
    {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    while (low < high)
    {
        if (arr[low] > arr[high])
        {
            mid = low + ((high - low) / 2U);
            if (arr[mid] >= arr[low])
            {
                low = mid + 1U;
            }
            else
            {
                high = mid;
            }
        }
        else
        {
            *result = arr[high];
            return 0;
        }
    }

    if (low == 0U)
    {
        *result = arr[0];
    }
    else
    {
        *result = arr[low - 1U];
    }

    return 0;
}

int main(void)
{
    int arr1[] = {5, 6, 7, 1, 2, 3, 4};
    int arr2[] = {3, 4, 5, 6, 7, 1, 2};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {7};
    int maxVal;
    int status;

    status = findMax(arr1, sizeof(arr1) / sizeof(arr1[0]), &maxVal);
    if (status == 0)
    {
        (void)printf("Maximum element: %d\n", maxVal);
    }
    else
    {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    status = findMax(arr2, sizeof(arr2) / sizeof(arr2[0]), &maxVal);
    if (status == 0)
    {
        (void)printf("Maximum element: %d\n", maxVal);
    }
    else
    {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    status = findMax(arr3, sizeof(arr3) / sizeof(arr3[0]), &maxVal);
    if (status == 0)
    {
        (void)printf("Maximum element: %d\n", maxVal);
    }
    else
    {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    status = findMax(arr4, sizeof(arr4) / sizeof(arr4[0]), &maxVal);
    if (status == 0)
    {
        (void)printf("Maximum element: %d\n", maxVal);
    }
    else
    {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    status = findMax(NULL, 0U, &maxVal);
    if (status != 0)
    {
        (void)printf("Correctly rejected invalid input\n");
    }

    return EXIT_SUCCESS;
}