#include <stdio.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void combinationUtil(int arr[], int data[], int start, int end, int index, int r)
{
    if (index == r)
    {
        printArray(data, r);
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i + 1, end, index + 1, r);
    }
}

void combinations(int arr[], int n, int r)
{
    int data[r];
    for(int i = 0; i < r; i++){
        data[i] = 0;
    }
    combinationUtil(arr, data, 0, n - 1, 0, r);
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int r = 3;
    combinations(arr, n, r);
    return 0;
}