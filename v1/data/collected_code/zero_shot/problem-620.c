#include<stdio.h>

void largestDivisibleSubset(int arr[], int n)
{
    if (n == 0)
        return;
 
    int count = 1, maxSubsetSize = 1;
    int lastElementIndex = 0;
    int *subsetSize = malloc(sizeof(int)*n);
    int *previousIndex = malloc(sizeof(int)*n);
 
    for (int i = 0; i < n; i++)
    {
        subsetSize[i] = 1;
        previousIndex[i] = -1;
    }
 
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
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
        subset[i] = arr[currentIndex];
        currentIndex = previousIndex[currentIndex];
    }
 
    printf("Largest Divisible Subset: ");
    for (int i = 0; i < maxSubsetSize; i++)
    {
        printf("%d ", subset[i]);
    }
 
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