#include <stdio.h>
#define MAX 500

/* Possible weaknesses found:
 *  expected 'int *' but argument is of type 'int (*)[500]'
 */
void BellNumberPartition(int BellNumbers[], int Partition[], int n)
{
    if(n == 0)
    {
        /* Possible weaknesses found:
         *  subscripted value is neither array nor pointer nor vector
         */
        BellNumbers[0] = Partition[0][0] = 1;
        return;
    }

    /* Possible weaknesses found:
     *  subscripted value is neither array nor pointer nor vector
     */
    Partition[0][0] = BellNumbers[0] = 1;

    for(int i=1; i<n; i++)
    {
        /* Possible weaknesses found:
         *  subscripted value is neither array nor pointer nor vector
         */
        Partition[i][0] = BellNumbers[i-1];

        for(int j=1; j<=i; j++)
        {
            /* Possible weaknesses found:
             *  subscripted value is neither array nor pointer nor vector
             */
            Partition[i][j] = Partition[i-1][j-1] + Partition[i][j-1];
        }

        /* Possible weaknesses found:
         *  subscripted value is neither array nor pointer nor vector
         */
        BellNumbers[i] = Partition[i][0] + Partition[i][i];
    }
}

int main()
{
    int n = 10;
    int BellNumbers[MAX];
    int Partition[MAX][MAX];

    /* Possible weaknesses found:
     *  passing argument 2 of 'BellNumberPartition' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    BellNumberPartition(BellNumbers, Partition, n);

    printf("The number of ways to partition a set of %d Bell numbers are: \n", n);
    
    for(int i=0; i<n; i++)
    {
        printf("BellNumber(%d) = %d\n", i, BellNumbers[i]);
    }

    return 0;
}