#include <stdio.h>
   /* Possible weaknesses found:
    *  include '<stdlib.h>' or provide a declaration of 'abs'
    */
  
int getSumOfAbsoluteDifferences(int arr[], int n)
{
    int sum = 0;
 
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            /* Possible weaknesses found:
             *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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