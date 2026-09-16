#include <stdio.h>
#include <stdlib.h>

int **remove_column(int **matrix, size_t rows, size_t cols, size_t col_to_remove)
{
    if (matrix == NULL || cols == 0 || col_to_remove >= cols)
    {
        return NULL;
    }

    int **new_matrix = malloc(rows * sizeof(*new_matrix));
    if (new_matrix == NULL)
    {
        return NULL;
    }

    size_t new_cols = cols - 1;

    for (size_t i = 0; i < rows; i++)
    {
        if (new_cols == 0)
        {
            new_matrix[i] = NULL;
            continue;
        }

        new_matrix[i] = malloc(new_cols * sizeof(*new_matrix[i]));
        if (new_matrix[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(new_matrix[j]);
            }
            free(new_matrix);
            return NULL;
        }

        size_t k = 0;
        for (size_t j = 0; j < cols; j++)
        {
            if (j != col_to_remove)
            {
                new_matrix[i][k] = matrix[i][j];
                k++;
            }
        }
    }

    return new_matrix;
}

void free_matrix(int **matrix, size_t rows)
{
    if (matrix == NULL)
    {
        return;
    }

    for (size_t i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(int **matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;

    int **matrix = malloc(rows * sizeof(*matrix));
    if (matrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(*matrix[i]));
        if (matrix[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        for (size_t j = 0; j < cols; j++)
        {
            matrix[i][j] = (int)(i * cols + j + 1);
        }
    }

    printf("Original matrix (%zu x %zu):\n", rows, cols);
    print_matrix(matrix, rows, cols);

    size_t col_to_remove = 2;

    int **new_matrix = remove_column(matrix, rows, cols, col_to_remove);
    if (new_matrix == NULL)
    {
        fprintf(stderr, "Failed to remove column %zu\n", col_to_remove);
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    printf("Matrix after removing column %zu:\n", col_to_remove);
    print_matrix(new_matrix, rows, cols - 1);

    free_matrix(matrix, rows);
    free_matrix(new_matrix, rows);

    return EXIT_SUCCESS;
}