#include <stdio.h>
#include <stdlib.h>

int findRotationCount(const int *arr, size_t n)
{
    size_t low = 0;
    size_t high = n - 1;

    if (n == 0)
    {
        return -1;
    }

    if (n == 1)
    {
        return 0;
    }

    while (low <= high)
    {
        if (arr[low] <= arr[high])
        {
            return (int)low;
        }

        size_t mid = low + (high - low) / 2;
        size_t next = (mid + 1) % n;
        size_t prev = (mid + n - 1) % n;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev])
        {
            return (int)mid;
        }

        if (arr[mid] <= arr[high])
        {
            high = mid - 1;
        }
        else if (arr[mid] >= arr[low])
        {
            low = mid + 1;
        }
    }

    return -1;
}

int main(void)
{
    int arr[] = {15, 18, 2, 3, 6, 12};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int rotations = findRotationCount(arr, n);

    if (rotations >= 0)
    {
        printf("Array is rotated %d times\n", rotations);
    }
    else
    {
        printf("Invalid array\n");
    }

    return EXIT_SUCCESS;
}