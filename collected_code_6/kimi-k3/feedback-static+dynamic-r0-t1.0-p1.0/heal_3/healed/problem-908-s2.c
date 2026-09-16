#include <stdio.h>
#include <limits.h>

int find_fixed_point(const int arr[], int size)
{
    if (arr == NULL || size <= 0)
    {
        return -1;
    }

    int low = 0;
    int high = size - 1;
    int result = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == mid)
        {
            result = mid;
            high = mid - 1;
        }
        else if (arr[mid] < mid)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return result;
}

int main(void)
{
    int arr[] = { -10, -5, 0, 3, 7 };
    int size = (int)(sizeof(arr) / sizeof(arr[0]));
    int result = find_fixed_point(arr, size);

    printf("%d\n", result);

    return 0;
}