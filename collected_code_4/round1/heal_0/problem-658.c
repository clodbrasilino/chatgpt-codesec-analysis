#include <stdio.h>
#define MAX_SIZE 100

int findMaxOccurrences(int arr[], int n)
{
    int maxCount = 0, maxElement = -1;
    for(int i = 0; i<n; i++)
    {
        int count = 1;
        for(int j = i+1; j<n; j++)
        {
            if(arr[j] == arr[i])
            {
               count++;
            }
        }
        if(count > maxCount)
        {
           maxCount = count;
           maxElement = arr[i];
        }
    }
    return maxElement;
}

int main()
{
    int arr[MAX_SIZE], i, n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    printf("Enter the array elements: ");
    for(i=0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }
        
    printf("Maximum Occurring Element: %d", findMaxOccurrences(arr, n));

    return 0;
}