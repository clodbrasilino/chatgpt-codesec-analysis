#include <stdio.h>
#define MAX 500

void BellNumberPartition(int BellNumbers[], int Partition[], int n)
{
    if(n == 0)
    {
        BellNumbers[0] = Partition[0][0] = 1;
        return;
    }

    Partition[0][0] = BellNumbers[0] = 1;

    for(int i=1; i<n; i++)
    {
        Partition[i][0] = BellNumbers[i-1];

        for(int j=1; j<=i; j++)
        {
            Partition[i][j] = Partition[i-1][j-1] + Partition[i][j-1];
        }

        BellNumbers[i] = Partition[i][0] + Partition[i][i];
    }
}

int main()
{
    int n = 10;
    int BellNumbers[MAX];
    int Partition[MAX][MAX];

    BellNumberPartition(BellNumbers, Partition, n);

    printf("The number of ways to partition a set of %d Bell numbers are: \n", n);
    
    for(int i=0; i<n; i++)
    {
        printf("BellNumber(%d) = %d\n", i, BellNumbers[i]);
    }

    return 0;
}