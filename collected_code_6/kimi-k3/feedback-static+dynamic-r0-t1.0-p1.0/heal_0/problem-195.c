#include <stdio.h>

int find_first_position(const int *arr, int size, int target)
{
    int left;
    int right;
    int mid;
    int result;

    if (arr == NULL || size <= 0)
    {
        return -1;
    }

    left = 0;
    right = size - 1;
    result = -1;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            result = mid;
            right = mid - 1;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return result;
}

int main(void)
{
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    int size;
    int target;
    int position;

    size = (int)(sizeof(arr) / sizeof(arr[0]));
    target = 2;
    position = find_first_position(arr, size, target);

    if (position != -1)
    {
        printf("First position of %d is at index %d\n", target, position);
    }
    else
    {
        printf("%d not found in the array\n", target);
    }

    target = 5;
    position = find_first_position(arr, size, target);

    if (position != -1)
    {
        printf("First position of %d is at index %d\n", target, position);
    }
    else
    {
        printf("%d not found in the array\n", target);
    }

    target = 7;
    position = find_first_position(arr, size, target);

    if (position != -1)
    {
        printf("First position of %d is at index %d\n", target, position);
    }
    else
    {
        printf("%d not found in the array\n", target);
    }

    return 0;
}