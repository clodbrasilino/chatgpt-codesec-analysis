#include <stdio.h>

#define N 100

void findMaxAveragePath(const int matrix[N][N], int n)
{
    int maxAvgPath[N] = {0};
    int i, j, maxSum = -1, sum, count;
    
    for (i = 0; i < n; i++)
    {
        sum = 0;
        count = 0;
        for (j = 0; j < n; j++)
        {
            sum += matrix[i][j];
            count++;
        }
        if (sum / count > maxSum)
        {
            maxSum = sum / count;
            for (j = 0; j < n; j++)
            {
                maxAvgPath[j] = matrix[i][j];
            }
        }
    }
    
    printf("The path with the maximum average is: ");
    for (j = 0; j < n; j++)
    {
        printf("%d ", maxAvgPath[j]);
    }
    printf("\n");
}

int main()
{
    int matrix[N][N] = {0};
    int n, i, j;
    
    printf("Enter the size of the square matrix: ");
    scanf("%d", &n);
    
    if (n > N || n <= 0)
    {
        printf("Invalid size of matrix\n");
        return -1;
    }
    
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