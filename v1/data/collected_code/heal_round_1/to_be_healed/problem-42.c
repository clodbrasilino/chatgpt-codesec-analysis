#include<stdio.h>
 
int sumOfRepeatedElements(int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = i + 1; j < size; j++)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] == arr[j])
                count++;
        }
        if (count >= 1)
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            sum += arr[i];
    }
    return sum;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 4, 5, 5, 6, 6, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = sumOfRepeatedElements(arr, size);
    printf("Sum of repeated elements: %d\n", result);
    return 0;
}