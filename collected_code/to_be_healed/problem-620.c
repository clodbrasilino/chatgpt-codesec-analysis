#include<stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void largestDivisibleSubset(int arr[], int n)
{
    if (n == 0)
        return;
 
    int count = 1, maxSubsetSize = 1;
    int lastElementIndex = 0;
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    int *subsetSize = malloc(sizeof(int)*n);
    int *previousIndex = malloc(sizeof(int)*n);
 
    for (int i = 0; i < n; i++)
    {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'subsetSize' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        subsetSize[i] = 1;
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'previousIndex' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        previousIndex[i] = -1;
    }
 
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] % arr[j] == 0 && subsetSize[i] < subsetSize[j] + 1)
            {
                subsetSize[i] = subsetSize[j] + 1;
                previousIndex[i] = j;
 
                if (subsetSize[i] > maxSubsetSize)
                {
                    maxSubsetSize = subsetSize[i];
                    lastElementIndex = i;
                }
            }
        }
    }
 
    int *subset = malloc(sizeof(int)*maxSubsetSize);
 
    int currentIndex = lastElementIndex;
    for (int i = maxSubsetSize - 1; i >= 0; i--)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[currentIndex]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  dereference of possibly-NULL 'subset' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        subset[i] = arr[currentIndex];
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'previousIndex' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  use of uninitialized value '*previousIndex_89 + _56' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        currentIndex = previousIndex[currentIndex];
    }
 
    printf("Largest Divisible Subset: ");
    for (int i = 0; i < maxSubsetSize; i++)
    {
        /* Possible weaknesses found:
         *  use of uninitialized value '*subset_93 + _59' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of possibly-NULL 'subset' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        printf("%d ", subset[i]);
    }
 
    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(subsetSize);
    free(previousIndex);
    free(subset);
}

int main()
{
    int arr[] = {1, 2, 3, 4, 6, 8, 12};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    largestDivisibleSubset(arr, n);
    
    return 0;
}