#include <stdio.h>

void findNumbersDivisible(int arr[], int size, int m, int n)
{
    printf("Numbers divisible by %d or %d: ", m, n);

    for (int i = 0; i < size; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] % m == 0 || arr[i] % n == 0)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d ", arr[i]);
        }
    }
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int m = 2;
    int n = 3;

    findNumbersDivisible(arr, size, m, n);
    
    return 0;
}