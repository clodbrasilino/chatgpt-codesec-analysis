#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int find_missing_number(const int *arr, size_t size, bool *error)
{
    size_t left;
    size_t right;
    size_t mid;
    int result;

    if (arr == NULL || error == NULL || size == 0)
    {
        if (error != NULL)
        {
            *error = true;
        }
        return -1;
    }

    *error = false;

    if (size == 1)
    {
        return arr[0] + 1;
    }

    left = 0;
    right = size - 1;

    if (arr[right] - arr[left] == (int)(right - left))
    {
        return arr[right] + 1;
    }

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (mid > 0 && arr[mid] - arr[mid - 1] > 1)
        {
            result = arr[mid - 1] + 1;
            return result;
        }

        if (arr[mid] - arr[0] == (int)mid)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    *error = true;
    return -1;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 6, 7, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    bool error = false;
    int missing;

    missing = find_missing_number(arr, size, &error);

    if (error)
    {
        fprintf(stderr, "Error: Invalid input or no missing number found\n");
        return 1;
    }

    printf("Missing number: %d\n", missing);

    return 0;
}