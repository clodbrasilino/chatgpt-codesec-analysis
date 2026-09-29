#include <stdio.h>

int sumInRange(int arr[], int size, int start, int end)
{
    int sum = 0;
    for (int i = start; i <= end; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int start = 2, end = 7;
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = sumInRange(arr, size, start, end);
    printf("Sum of numbers between indices %d and %d is %d\n", start, end, result);

    return 0;
}