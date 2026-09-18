#include <stdio.h>
#include <limits.h>

void maxProductPair(int arr[], int arr_size, int* a, int* b)
{
    if (arr_size < 2)
    {
        printf("No pairs exist\n");
        return;
    }
    int x = INT_MIN, y = INT_MIN;
    for (int i = 0; i < arr_size; i++)
    {
        if (arr[i] > x)
        {
            y = x;
            x = arr[i];
        }
        else if (arr[i] > y)
            y = arr[i];
    }
    *a = x;
    *b = y;
}

int main()
{
    int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr)/sizeof(arr[0]);
    int a,b;
    maxProductPair(arr, n, &a, &b);
    if(a!=INT_MIN && b!=INT_MIN)
        printf("Max product pair is {%d, %d}", a, b);
    return 0;
}