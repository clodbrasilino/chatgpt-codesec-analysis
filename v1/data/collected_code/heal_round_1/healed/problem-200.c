#include <stdio.h>

void findMaxIndexes(const int arr[], int size, int maxIndex[])
{
    int maxVal = arr[0];
    int numMax = 1;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > maxVal)
        {
            maxVal = arr[i];
            numMax = 1;
        }
        else if (arr[i] == maxVal)
        {
            maxIndex[numMax++] = i;
        }
    }

    maxIndex[0] = numMax;
}

int main()
{
    const int arr[] = {3, 7, 2, 5, 5, 6, 2, 8, 9, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int maxIndexes[size];

    findMaxIndexes(arr, size, maxIndexes);

    printf("Maximum values found at index positions: ");

    for (int i = 1; i <= maxIndexes[0]; i++)
    {
        printf("%d ", maxIndexes[i]);
    }

    return 0;
}