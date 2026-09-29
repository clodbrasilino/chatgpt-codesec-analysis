#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void findFrequency(int arr[MAX][MAX], int m, int n)
{
    int freq[MAX] = {0};

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            freq[arr[i][j]]++;
        }
    }

    for(int i = 0; i < MAX; i++)
    {
        if(freq[i] != 0)
        {
            printf("%d occurs %d times\n", i, freq[i]);
        }
    }
}

int main()
{
    int m,n;
    printf("Enter the rows and columns of the 2D array: ");
    scanf("%d %d",&m,&n);

    int arr[MAX][MAX];
    printf("Enter elements of the 2D array: ");

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    findFrequency(arr, m, n);

    return 0;
}