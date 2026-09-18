#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isSubsetSumDivisible(int arr[], int n, int m)
{
    if(m == 0)
        return true;
        
    if(n == 0 && m != 0)
        return false;
 
    if(arr[n-1] > m)
        return isSubsetSumDivisible(arr, n-1, m);
        
    return isSubsetSumDivisible( arr, n-1, m ) 
           || isSubsetSumDivisible( arr, n-1, m-arr[n-1] );
}
 
int main()
{
    int arr[] = {3, 1, 7, 5};
    int m = 6;
    int n = sizeof(arr)/sizeof(arr[0]);
    
    if(isSubsetSumDivisible(arr, n, m) == true)
        printf("There exists a subset with sum divisible by %d", m);
    else
        printf("No subset with sum divisible by %d", m);
  
   return 0;
}