#include <stdio.h>

void findUnion(int arr1[], int size1, int arr2[], int size2)
{
    int union_arr[size1 + size2];
    int i, j, k;
    
    // Initializing union array with elements from arr1
    for(i = 0; i < size1; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        union_arr[i] = arr1[i];
    }
    
    // Checking duplicate elements from arr2 and adding to union array
    for(j = 0; j < size2; j++)
    {
        int isDuplicate = 0;
        for(k = 0; k < size1 + j; k++)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if(arr2[j] == union_arr[k])
            {
                isDuplicate = 1;
                break;
            }
        }
        
        if(!isDuplicate)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            union_arr[i] = arr2[j];
            i++;
        }
    }
    
    // Printing the union of elements
    printf("Union of the given tuples: ");
    for(int m = 0; m < i; m++)
    {
        printf("%d ", union_arr[m]);
    }
}

int main()
{
    int arr1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {4, 5, 6, 7, 8};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    findUnion(arr1, size1, arr2, size2);
    
    return 0;
}