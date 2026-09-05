#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  expected 'const int * const*' but argument is of type 'int **'
 */
int *extract_column(const int *const *matrix, size_t rows, size_t cols, size_t col_index)
{
    int *column;
    size_t i;

    if (matrix == NULL || rows == 0 || cols == 0 || col_index >= cols)
    {
        return NULL;
    }

    column = malloc(rows * sizeof(*column));
    if (column == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        if (matrix[i] == NULL)
        {
            free(column);
            return NULL;
        }
        column[i] = matrix[i][col_index];
    }

    return column;
}

void free_matrix(int **matrix, size_t rows)
{
    size_t i;

    if (matrix == NULL)
    {
        return;
    }

    for (i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;
    size_t col_index = 2;
    int **matrix;
    int *column;
    size_t i;
    size_t j;

    matrix = malloc(rows * sizeof(*matrix));
    if (matrix == NULL)
    {
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(*matrix[i]));
        if (matrix[i] == NULL)
        {
            free_matrix(matrix, i);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            matrix[i][j] = (int)(i * cols + j + 1);
        }
    }

    /* Possible weaknesses found:
     *  passing argument 1 of 'extract_column' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    column = extract_column(matrix, rows, cols, col_index);
    if (column == NULL)
    {
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    printf("Column %zu:\n", col_index);
    for (i = 0; i < rows; i++)
    {
        printf("%d\n", column[i]);
    }

    free(column);
    free_matrix(matrix, rows);

    return EXIT_SUCCESS;
}