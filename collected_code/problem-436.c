#include <stdio.h>

void printNegativeNumbers(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < 0)
        {
            printf("%d\n", arr[i]);
        }
    }
}