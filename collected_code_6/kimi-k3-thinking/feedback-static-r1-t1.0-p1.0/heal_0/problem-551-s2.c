#include <stdio.h>
#include <stdlib.h>

int extract_column(int rows, int cols, const int matrix[][cols], int col_index, int *result)
{
    int i;

    if (matrix == NULL || result == NULL)
    {
        return -1;
    }

    if (rows <= 0 || cols <= 0)
    {
        return -1;
    }

    if (col_index < 0 || col_index >= cols)
    {
        return -1;
    }

    for (i = 0; i < rows; i++)
    {
        result[i] = matrix[i][col_index];
    }

    return 0;
}

int main(void)
{
    const int rows = 3;
    const int cols = 4;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int col_index = 2;
    int *column = NULL;
    int i;

    column = (int *)malloc((size_t)rows * sizeof(int));
    if (column == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (extract_column(rows, cols, matrix, col_index, column) != 0)
    {
        fprintf(stderr, "Error: invalid column index %d\n", col_index);
        free(column);
        column = NULL;
        return EXIT_FAILURE;
    }

    printf("Column %d:\n", col_index);
    for (i = 0; i < rows; i++)
    {
        printf("%d\n", column[i]);
    }

    free(column);
    column = NULL;

    return EXIT_SUCCESS;
}