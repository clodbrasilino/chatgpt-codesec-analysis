#include <stdio.h>
#define SIZE 100

void find_frequency(int arr[], int n)
{
    int freq[SIZE], count, i, j;

    for(i = 0; i < SIZE; i++) {
        freq[i] = -1;
    }

    for(i = 0; i < n; i++)
    {
        count = 1;
        for(j = i+1; j < n; j++)
        {
            if(arr[i] == arr[j])
            {
                count++;
                
                freq[j] = 0;
            }
        }

        if(freq[i] != 0)
        {
            freq[i] = count;
        }
    }

    for(i = 0; i < n; i++)
    {
        if(freq[i] != 0)
        {
            printf("%d occurs %d times\n", arr[i], freq[i]);
        }
    }
}

int main()
{
    int n, i;
    int arr[SIZE];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements: \n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    find_frequency(arr, n);

    return 0;
}