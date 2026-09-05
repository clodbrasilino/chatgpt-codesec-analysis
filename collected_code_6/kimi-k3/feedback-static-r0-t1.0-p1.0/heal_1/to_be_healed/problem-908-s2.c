#include <stdio.h>

int find_fixed_point(const int arr[], int size)
{
    int low = 0;
    int high = size - 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    int mid;

    if (arr == NULL || size <= 0)
    {
        return -1;
    }

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] == mid)
        {
            return mid;
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

    return -1;
}

int main(void)
{
    int arr[] = { -10, -5, 0, 3, 7 };
    int size = (int)(sizeof(arr) / sizeof(arr[0]));
    int result = find_fixed_point(arr, size);

    if (result != -1)
    {
        printf("Fixed point is: %d\n", result);
    }
    else
    {
        printf("No fixed point found\n");
    }

    return 0;
}