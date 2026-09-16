#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  */

int countRotations(const int arr[], int n)
{
    int low;
    int high;

    if (arr == NULL || n <= 0)
    {
        return -1;
    }

    low = 0;
    high = n - 1;

    while (low <= high)
    {
        int mid;
        int next;
        int prev;

        if (arr[low] <= arr[high])
        {
            return low;
        }

        mid = low + (high - low) / 2;
        next = (mid + 1) % n;
        prev = (mid + n - 1) % n;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev])
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