#include <stdio.h>
#include <stdlib.h>

int *extract_column(int **matrix, size_t rows, size_t cols, size_t column)
{
    int *column_data;
    size_t i;

    if (matrix == NULL || rows == 0 || cols == 0 || column >= cols)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        if (matrix[i] == NULL)
        {
            return NULL;
        }
    }

    column_data = malloc(rows * sizeof(*column_data));
    if (column_data == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        column_data[i] = matrix[i][column];
    }

    return column_data;
}

int **create_matrix(size_t rows, size_t cols)
{
    int **matrix;
    size_t i;

    if (rows == 0 || cols == 0)
    {
        return NULL;
    }

    matrix = malloc(rows * sizeof(*matrix));
    if (matrix == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(*matrix[i]));
        if (matrix[i] == NULL)
        {
            while (i > 0)
            {
                i--;
                free(matrix[i]);
            }
            free(matrix);
            return NULL;
        }
    }

    return matrix;
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
    const size_t rows = 4;
    const size_t cols = 3;
    const size_t column = 1;
    int **matrix;
    int *extracted;
    size_t i;
    size_t j;

    matrix = create_matrix(rows, cols);
    if (matrix == NULL)
    {
        fprintf(stderr, "Error: failed to create matrix\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            matrix[i][j] = (int)(i * cols + j + 1);
        }
    }

    printf("Matrix:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    extracted = extract_column(matrix, rows, cols, column);
    if (extracted == NULL)
    {
        fprintf(stderr, "Error: failed to extract column %zu\n", column);
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    printf("Column %zu:\n", column);
    for (i = 0; i < rows; i++)
    {
        printf("%d\n", extracted[i]);
    }

    free(extracted);
    free_matrix(matrix, rows);

    return EXIT_SUCCESS;
}