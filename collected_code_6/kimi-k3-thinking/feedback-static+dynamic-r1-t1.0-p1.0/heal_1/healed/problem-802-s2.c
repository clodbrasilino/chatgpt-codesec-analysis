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

    while (low < high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] > arr[high])
        {
            low = mid + 1;
        }
        else if (arr[mid] < arr[high])
        {
            high = mid;
        }
        else
        {
            high = high - 1;
        }
    }

    return low;
}

int main(void)
{
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {5, 1, 2, 3, 4};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));
    int n3 = (int)(sizeof(arr3) / sizeof(arr3[0]));
    int rotations;

    rotations = countRotations(arr1, n1);
    if (rotations < 0)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }
    printf("Array 1 rotations: %d\n", rotations);

    rotations = countRotations(arr2, n2);
    if (rotations < 0)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }
    printf("Array 2 rotations: %d\n", rotations);

    rotations = countRotations(arr3, n3);
    if (rotations < 0)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }
    printf("Array 3 rotations: %d\n", rotations);

    return 0;
}