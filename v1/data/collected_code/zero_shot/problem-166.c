#include <stdio.h>

int countPairs(int arr[], int size)
{
    int count = 0;
    
    for (int i = 0; i < size-1; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if ((arr[i] ^ arr[j]) % 2 == 0)
                count++;
        }
    }
    
    return count;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr)/sizeof(arr[0]);
    
    int pairsCount = countPairs(arr, size);
    
    printf("Pairs with xor as an even number: %d", pairsCount);
    
    return 0;
}