#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int a[], int size)
{
    int maxSoFar = INT_MIN, maxEndingHere = 0;
 
    for (int i = 0; i < size; i++)
    {
        maxEndingHere = maxEndingHere + a[i];
        if (maxSoFar < maxEndingHere)
            maxSoFar = maxEndingHere;
 
        if (maxEndingHere < 0)
            maxEndingHere = 0;
    }
    return maxSoFar;
}
 
int main()
{
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int size = sizeof(arr)/sizeof(arr[0]);
    int result = maxSubArraySum(arr, size);
    printf("Maximum contiguous sum is %d\n", result);
    return 0;
}