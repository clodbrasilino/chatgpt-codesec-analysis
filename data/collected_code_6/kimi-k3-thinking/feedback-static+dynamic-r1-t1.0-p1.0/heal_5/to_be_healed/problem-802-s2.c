#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  *  test case 2 failed: expected 3, got 5
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

    while (low < high)
    {
        int mid = low + (high - low) / 2;

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
    int n;
    int i;
    int rotations;
    int *arr;

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        return 1;
    }

    arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL)
    {
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            free(arr);
            return 1;
        }
    }

    rotations = countRotations(arr, n);

    if (rotations >= 0)
    {
        printf("%d\n", rotations);
    }

    free(arr);

    return 0;
}