#include <stdio.h>
#define N 100

void findMaxAveragePath(int matrix[N][N], int n)
{
    int i, j, maxSum = -1, sum, count;
    int maxAvgPath[N];
    
    for (i = 0; i < n; i++)
    {
        sum = 0;
        count = 0;
        for (j = 0; j < n; j++)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'matrix[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            sum += matrix[i][j];
            count++;
        }
        if (sum / count > maxSum)
        {
            maxSum = sum / count;
            for (j = 0; j < n; j++)
            {
                /* Possible weaknesses found:
                 *  Cannot determine that 'matrix[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                maxAvgPath[j] = matrix[i][j];
            }
        }
    }
    
    printf("The path with the maximum average is: ");
    for (j = 0; j < n; j++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'maxAvgPath[j]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", maxAvgPath[j]);
    }
    printf("\n");
}

int main()
{
    int matrix[N][N], n, i, j;
    
    printf("Enter the size of the square matrix: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    findMaxAveragePath(matrix, n);
    
    return 0;
}
