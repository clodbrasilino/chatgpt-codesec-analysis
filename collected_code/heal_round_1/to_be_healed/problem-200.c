#include <stdio.h>

void findMaxIndexes(int arr[], int size, int maxIndex[])
{
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int maxVal = arr[0];
    int numMax = 1;
    
    for (int i = 1; i < size; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] > maxVal)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            maxVal = arr[i];
            numMax = 1;
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (arr[i] == maxVal)
        {
            maxIndex[numMax++] = i;
        }
    }
    
    maxIndex[0] = numMax;
}

int main()
{
    int arr[] = {3, 7, 2, 5, 5, 6, 2, 8, 9, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int maxIndexes[size];
    
    findMaxIndexes(arr, size, maxIndexes);
    
    printf("Maximum values found at index positions: ");
    
    /* Possible weaknesses found:
     *  Cannot determine that 'maxIndexes[0]' is initialized [premium-bughuntingUninit]
     */
    for (int i = 1; i <= maxIndexes[0]; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'maxIndexes[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", maxIndexes[i]);
    }
    
    return 0;
}