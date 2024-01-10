#include <stdio.h>

int findTriplet(int arr[], int n, int given)
{
    // Fix the first element as A[i]
    for (int i = 0; i < n - 2; i++)
    {
        // Fix the second element as A[j]
        for (int j = i + 1; j < n - 1; j++)
        {
            // Fix the third element as A[k]
            for (int k = j + 1; k < n; k++)
            {
                // Check if sum of triplet equals given value
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[k]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                if (arr[i] + arr[j] + arr[k] == given)
                    return 1; // Triplet found
            }
        }
    }
    
    return 0; // No triplet found
}

int main()
{
    int arr[] = {1, 4, 2, 7, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int given = 10;
    
    if (findTriplet(arr, n, given))
        printf("Triplet found");
    else
        printf("No triplet found");
    
    return 0;
}