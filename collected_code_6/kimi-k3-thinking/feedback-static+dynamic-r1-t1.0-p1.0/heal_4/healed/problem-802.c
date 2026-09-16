#include <stdio.h>

int countRotations(const int arr[], int n)
{
    int i;
    int minIndex;

    if (arr == NULL || n <= 0)
    {
        return -1;
    }

    minIndex = 0;

    for (i = 1; i < n; i++)
    {
        if (arr[i] < arr[minIndex])
        {
            minIndex = i;
        }
    }

    return minIndex;
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