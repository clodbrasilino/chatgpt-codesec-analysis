#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int findArrayGCD(int arr[], int n)
{
    int result = arr[0];
    int i;
    for (i = 1; i < n; i++)
    {
        result = gcd(result, arr[i]);
    }
    return result;
}

int main()
{
    int n;
    int i;
    int *arr;
    int result;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    result = findArrayGCD(arr, n);
    printf("GCD of the array elements is: %d\n", result);

    free(arr);
    return 0;
}