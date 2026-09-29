#include <stdio.h>
  
int getSumOfAbsoluteDifferences(int arr[], int n)
{
    int sum = 0;
 
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            sum += abs(arr[i] - arr[j]);
        }
    }
 
    return sum;
}
 
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    int sum = getSumOfAbsoluteDifferences(arr, n);
 
    printf("Sum of absolute differences: %d", sum);
 
    return 0;
}