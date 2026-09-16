#include <stdio.h>
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
    printf("%d\n", result);

    result = countRotations(arr2, n2);
    printf("%d\n", result);

    result = countRotations(arr3, n3);
    printf("%d\n", result);

    result = countRotations(arr4, n4);
    printf("%d\n", result);

    return 0;
}