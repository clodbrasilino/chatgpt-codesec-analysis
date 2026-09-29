#include <stdio.h>

void shellSort(int arr[], int n)
{
    for (int interval = n/2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < n; i += 1)
        {
            int temp = arr[i];
            int j;           
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval)
            {
                arr[j] = arr[j - interval];
            }
            arr[j] = temp;
        }
    }
}

int main()
{
    int arr[] = {12, 34, 54, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    shellSort(arr, n);
    printf("Array after sorting: \n");
    for (int i=0; i<n; i++)
        printf("%d ", arr[i]);
    return 0;
}