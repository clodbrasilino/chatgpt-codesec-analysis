#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected -1, got <no output>
  *  test case 2 failed: expected 0, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

int find_fixed_point(const int arr[], int size)
{
    int low = 0;
    int high = size - 1;
    int result = -1;

    if (arr == NULL || size <= 0)
    {
        return -1;
    }

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