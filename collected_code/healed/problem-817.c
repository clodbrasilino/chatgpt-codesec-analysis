#include <stdio.h>

void findNumbersDivisible(const int arr[], const int size, const int m, const int n)
{
    printf("Numbers divisible by %d or %d: ", m, n);

    for (int i = 0; i < size; i++)
    {
        if (arr[i] % m == 0 || arr[i] % n == 0)
        {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
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