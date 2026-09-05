#include <stdio.h>
#include <stdlib.h>

void rearrange(int arr[], int n)
{
    int left = 0;
    int right = n - 1;
    int temp;
    
    if (arr == NULL || n <= 0)
    {
        return;
    }
    
    while (left <= right)
    {
        while (left <= right && arr[left] < 0)
        {
            left++;
        }
        while (left <= right && arr[right] >= 0)
        {
            right--;
        }
        
        if (left < right)
        {
            temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void)
{
    int arr[] = {-12, 11, -13, -5, 6, -7, 5, -3, -6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;
    
    if (n == 0)
    {
        return 1;
    }
    
    printf("Original array: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    rearrange(arr, n);
    
    printf("Rearranged array: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}