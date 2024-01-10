#include <stdio.h>

int minJumps(int arr[], int n)
{
    if (n <= 1)
        return 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[0] == 0)
        return -1;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int maxReach = arr[0];
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int steps = arr[0];
    int jumps = 1;
    
    for (int i = 1; i < n; i++)
    {
        if (i == n - 1)
            return jumps;
        
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
         */
        maxReach = max(maxReach, i + arr[i]);
        steps--;
        
        if (steps == 0)
        {
            jumps++;
            
            if (i >= maxReach)
                return -1;
            
            steps = maxReach - i;
        }
    }
    
    return -1;
}

int main()
{
    int arr[] = {2, 3, 1, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Minimum number of jumps: %d\n", minJumps(arr, n));
    
    return 0;
}