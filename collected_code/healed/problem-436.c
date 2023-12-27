#include <stdio.h>

void printNegativeNumbers(const int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < 0)
        {
            printf("%d\n", arr[i]);
        }
    }
}

int main() 
{
    int numbers[] = {1, -2, 3, -4, 5};
    int arraySize = sizeof(numbers)/sizeof(numbers[0]);

    printNegativeNumbers(numbers, arraySize);

    return 0;
}