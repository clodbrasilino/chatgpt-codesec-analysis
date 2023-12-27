#include<stdio.h>

int sumOfRepeatedElements(const int arr[], const int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] == arr[j])
                count++;
        }
        if (count >= 1)
            sum += arr[i];
    }
    return sum;
}

int main()
{
    const int arr[] = {1, 2, 3, 4, 4, 5, 5, 6, 6, 6};
    const int size = sizeof(arr) / sizeof(arr[0]);
    int result = sumOfRepeatedElements(arr, size);
    printf("Sum of repeated elements: %d\n", result);
    return 0;
}