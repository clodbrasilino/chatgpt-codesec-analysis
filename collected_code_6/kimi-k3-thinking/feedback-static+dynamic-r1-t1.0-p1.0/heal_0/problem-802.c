#include <stdio.h>

int countRotations(const int arr[], int n)
{
    int low;
    int high;
    int mid;

    if (arr == NULL || n <= 0)
    {
        return -1;
    }

    low = 0;
    high = n - 1;

    while (low <= high)
    {
        if (arr[low] <= arr[high])
        {
            return low;
        }

        mid = low + (high - low) / 2;

        if (mid < high && arr[mid] > arr[mid + 1])
        {
            return mid + 1;
        }

        if (mid > low && arr[mid - 1] > arr[mid])
        {
            return mid;
        }

        if (arr[mid] >= arr[low])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return 0;
}

int main(void)
{
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int arr2[] = {7, 9, 11, 12, 5};
    int arr3[] = {7, 9, 11, 12, 15};
    int arr4[] = {42};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));
    int n3 = (int)(sizeof(arr3) / sizeof(arr3[0]));
    int n4 = (int)(sizeof(arr4) / sizeof(arr4[0]));
    int result;

    result = countRotations(arr1, n1);
    if (result >= 0)
    {
        printf("Rotations for array 1: %d\n", result);
    }
    else
    {
        printf("Invalid input for array 1\n");
    }

    result = countRotations(arr2, n2);
    if (result >= 0)
    {
        printf("Rotations for array 2: %d\n", result);
    }
    else
    {
        printf("Invalid input for array 2\n");
    }

    result = countRotations(arr3, n3);
    if (result >= 0)
    {
        printf("Rotations for array 3: %d\n", result);
    }
    else
    {
        printf("Invalid input for array 3\n");
    }

    result = countRotations(arr4, n4);
    if (result >= 0)
    {
        printf("Rotations for array 4: %d\n", result);
    }
    else
    {
        printf("Invalid input for array 4\n");
    }

    return 0;
}