#include <stdio.h>

void findSecondSmallest(int arr[], int n)
{
    if (n < 2)
    {
        printf("Invalid input\n");
        return;
    }

    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int smallest = arr[0];
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int secondSmallest = arr[0];

    for (int i = 1; i < n; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] < smallest)
        {
            secondSmallest = smallest;
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            smallest = arr[i];
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (arr[i] < secondSmallest && arr[i] != smallest)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            secondSmallest = arr[i];
        }
    }

    printf("The second smallest number is %d\n", secondSmallest);
}

int main()
{
    int arr[] = {5, 2, 8, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    findSecondSmallest(arr, n);

    return 0;
}