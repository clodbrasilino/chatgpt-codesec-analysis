#include <stdio.h>

void filterEvenNumbers(const int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(arr[i] % 2 == 0)
        {
            printf("%d ", arr[i]);
        }
    }
}

int main()
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    filterEvenNumbers(numbers, size);

    return 0;
}