#include<stdio.h>

int minPathSum(int triangle[][5], int row, int col)
{
    if (row == 4)
    {
        return triangle[row][col];
    }
    
    int left = minPathSum(triangle, row + 1, col);
    int right = minPathSum(triangle, row + 1, col + 1);
    
    if (left < right)
    {
        return triangle[row][col] + left;
    }
    else
    {
        return triangle[row][col] + right;
    }
}

int main()
{
    int triangle[5][5] = {{2},
                          {3, 4},
                          {6, 5, 7},
                          {4, 1, 8, 3}};
    
    int result = minPathSum(triangle, 0, 0);
    
    printf("Minimum total path sum: %d\n", result);
    
    return 0;
}