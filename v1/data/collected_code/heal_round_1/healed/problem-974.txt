#include<stdio.h>

int minPathSum(const int triangle[5][5], int row, int col)
{
    if (row == 4)
    {
        return triangle[row][col];
    }
    
    int left = minPathSum(triangle, row + 1, col);
    int right = minPathSum(triangle, row + 1, col + 1);
    
    return (left < right) ? triangle[row][col] + left : triangle[row][col] + right;
}

int main()
{
    const int triangle[5][5] = {{2, 0, 0, 0, 0},
                          {3, 4, 0, 0, 0},
                          {6, 5, 7, 0, 0},
                          {4, 1, 8, 3, 0},
                          {0, 0, 0, 0, 0}};
    
    int result = minPathSum(triangle, 0, 0);
    
    printf("Minimum total path sum: %d\n", result);
    
    return 0;
}