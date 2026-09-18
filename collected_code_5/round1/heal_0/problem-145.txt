#include <stdio.h>
#include <limits.h>

int findMaxDiff(int arr[], int n)
{
    int max = INT_MIN, min = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];

        if (arr[i] < min)
            min = arr[i];
    }

    return (max - min);
}

int main(void)
{
    int arr[] = {12, 5, 1, 7, 3, 6, 10};
    int size = sizeof(arr)/sizeof(arr[0]);

    int maxDiff = findMaxDiff(arr, size);

    printf("The maximum difference is %d\n", maxDiff);

    return 0;
}