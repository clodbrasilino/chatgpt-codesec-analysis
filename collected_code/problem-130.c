#include <stdio.h>
#define MAX_SIZE 100

int findMaxFrequency(int arr[], int size)
{
    int maxFreq = 0;
    int maxFreqItem = arr[0];

    for (int i = 0; i < size; i++)
    {
        int freq = 1;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] == arr[i])
                freq++;
        }

        if (freq > maxFreq)
        {
            maxFreq = freq;
            maxFreqItem = arr[i];
        }
    }

    return maxFreqItem;
}

int main()
{
    int arr[MAX_SIZE];
    int size;

    printf("Enter the size of the list: ");
    scanf("%d", &size);

    printf("Enter the elements of the list:\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    int maxFreqItem = findMaxFrequency(arr, size);
    printf("The item with maximum frequency is: %d\n", maxFreqItem);

    return 0;
}