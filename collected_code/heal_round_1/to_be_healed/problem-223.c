#include<stdio.h>

int isMajority(int arr[], int n, int element)
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == element)
            count++;
    }

    if (count > n / 2)
        return 1;
    else
        return 0;
}

int findMajority(int arr[], int n)
{
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[n/2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int majorityElement = arr[n / 2];

    if (isMajority(arr, n, majorityElement))
        return majorityElement;
    else
        return -1;
}

int main()
{
    int arr[] = {1, 2, 2, 2, 3, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = findMajority(arr, n);

    if (result != -1)
        printf("Majority element is %d\n", result);
    else
        printf("No majority element\n");

    return 0;
}