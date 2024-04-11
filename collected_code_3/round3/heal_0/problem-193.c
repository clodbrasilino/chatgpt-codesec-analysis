#include <stdio.h>

void removeDuplicates(int arr[], int *n)
{
    if (*n == 0 || *n == 1)
        return;

    int temp[*n];

    int j = 0;
    for (int i = 0; i < *n - 1; i++)
        if (arr[i] != arr[i + 1])
            temp[j++] = arr[i];

    temp[j++] = arr[*n - 1];

    for (int i = 0; i < j; i++)
        arr[i] = temp[i];

    *n = j;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    removeDuplicates(arr, &n);

    printArray(arr, n);

    return 0;
}