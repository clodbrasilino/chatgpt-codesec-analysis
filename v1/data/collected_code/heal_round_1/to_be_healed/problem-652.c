#include <stdio.h>

void flattenTupleMatrix(int mat[][3], int row, int col)
{
    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'mat[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("(%d, %d) ", mat[i][j], j);
        }
    }
}

int main()
{
    int mat[][3] = {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};
    int row = sizeof(mat) / sizeof(mat[0]);
    int col = sizeof(mat[0]) / sizeof(int);

    flattenTupleMatrix(mat, row, col);

    return 0;
}