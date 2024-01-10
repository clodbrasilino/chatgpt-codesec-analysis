#include <stdio.h>

int findExtraElementIndex(int arr1[], int arr2[], int arr_size)
{
    int i;
    for (i = 0; i < arr_size; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr1[i] != arr2[i])
        {
            return i;
        }
    }
    
    // If no extra element found, return -1
    return -1;
}

int main()
{
    int arr1[] = {1, 2, 3, 4, 5, 6};
    int arr2[] = {1, 2, 3, 4, 6};
    int arr_size = sizeof(arr2) / sizeof(arr2[0]);
    
    int extraIndex = findExtraElementIndex(arr1, arr2, arr_size);
    
    printf("Extra element index: %d\n", extraIndex);
    
    return 0;
}