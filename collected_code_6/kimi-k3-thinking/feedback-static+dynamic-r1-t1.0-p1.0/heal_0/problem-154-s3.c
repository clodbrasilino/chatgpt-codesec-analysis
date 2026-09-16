#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int *extract_elements(const int *const *matrix, size_t rows, size_t cols, size_t index)
{
    int *result;
    size_t i;

    if (matrix == NULL || rows == 0U || cols == 0U || index >= cols)
    {
        return NULL;
    }

    if (rows > SIZE_MAX / sizeof(*result))
    {
        return NULL;
    }

    result = malloc(rows * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0U; i < rows; i++)
    {
        if (matrix[i] == NULL)
        {
            free(result);
            return NULL;
        }
        result[i] = matrix[i][index];
    }

    return result;
}

static void free_matrix(int **matrix, size_t rows)
{
    size_t i;

    if (matrix == NULL)
    {
        return;
    }

    for (i = 0U; i < rows; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}

int main(void)
{
    const size_t rows = 3U;
    const size_t cols = 3U;
    const size_t index = 1U;
    int **matrix;
    int *extracted;
    size_t i;
    size_t j;

    matrix = malloc(rows * sizeof(*matrix));
    if (matrix == NULL)
    {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(**matrix));
        if (matrix[i] == NULL)
        {
            free_matrix(matrix, i);
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < rows; i++)
    {
        for (j = 0U; j < cols; j++)
        {
            matrix[i][j] = (int)((i * cols) + j + 1U);
        }
    }

    extracted = extract_elements((const int *const *)matrix, rows, cols, index);
    if (extracted == NULL)
    {
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    printf("Matrix:\n");
    for (i = 0U; i < rows; i++)
    {
        for (j = 0U; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Elements at index %zu:\n", index);
    for (i = 0U; i < rows; i++)
    {
        printf("%d ", extracted[i]);
    }
    printf("\n");

    free(extracted);
    extracted = NULL;
    free_matrix(matrix, rows);
    matrix = NULL;

    return EXIT_SUCCESS;
}