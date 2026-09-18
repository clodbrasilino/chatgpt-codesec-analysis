#include <stdio.h>
#include <limits.h>

int find_max_sum(int arr[], int n)
{
    int max_sum = INT_MIN;
    int temp_sum = 0;

    for (int i = 0; i < n; i++)
    {
        temp_sum += arr[i];

        if (max_sum < temp_sum)
        {
            max_sum = temp_sum;
        }

        if (temp_sum < 0)
        {
            temp_sum = 0;
        }
    }

    return max_sum;
}

int main()
{
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr)/sizeof(arr[0]);
    int max_sum = find_max_sum(arr, n);
    printf("Maximum contiguous sum is %d\n", max_sum);
    
    return 0;
}