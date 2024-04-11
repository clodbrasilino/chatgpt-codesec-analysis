#include <stdio.h>
#include <limits.h>

int maxDifference(int arr[], int arr_size)
{
    int max_diff = arr[1] - arr[0];
    int i, j;
    for (i = 0; i < arr_size; i++)
    {
        for (j = i+1; j < arr_size; j++)
        {    
            if (arr[j] - arr[i] > max_diff)
                max_diff = arr[j] - arr[i];
        }
    }        
    return max_diff;
}

int main()
{
    int arr[] = {1, 2, 90, 10, 110};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum difference is %d", maxDifference(arr, size));
    return 0;
}