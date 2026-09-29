#include <stdio.h>
#include <stdlib.h>

int **generate_spiral_matrix(int n);
void free_matrix(int **matrix, int n);
void print_matrix(int **matrix, int n);

int **generate_spiral_matrix(int n)
{
    int **matrix;
    int top;
    int bottom;
    int left;
    int right;
    int value;
    int i;

    if (n <= 0)
    {
        return NULL;
    }

    matrix = malloc((size_t)n * sizeof(int *));
    if (matrix == NULL)
    {
        return NULL;
    }

    for (i = 0; i < n; i++)
    {
        matrix[i] = malloc((size_t)n * sizeof(int));
        if (matrix[i] == NULL)
        {
            free_matrix(matrix, i);
            return NULL;
        }
    }

    top = 0;
    bottom = n - 1;
    left = 0;
    right = n - 1;
    value = 1;

    while (top <= bottom && left <= right)
    {
        for (i = left; i <= right; i++)
        {
            matrix[top][i] = value;
            value++;
        }
        top++;

        for (i = top; i <= bottom; i++)
        {
            matrix[i][right] = value;
            value++;
        }
        right--;

        if (top <= bottom)
        {
            for (i = right; i >= left; i--)
            {
                matrix[bottom][i] = value;
                value++;
            }
            bottom--;
        }

        if (left <= right)
        {
            for (i = bottom; i >= top; i--)
            {
                matrix[i][left] = value;
                value++;
            }
            left++;
        }
    }

    return matrix;
}

void free_matrix(int **matrix, int n)
{
    int i;

    if (matrix == NULL)
    {
        return;
    }

    for (i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(int **matrix, int n)
{
    int i;
    int j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (printf("%4d ", matrix[i][j]) < 0)
            {
                return;
            }
        }
        if (printf("\n") < 0)
        {
            return;
        }
    }
}

int main(void)
{
    int n;
    int **matrix;

    n = 5;

    matrix = generate_spiral_matrix(n);
    if (matrix == NULL)
    {
        fprintf(stderr, "Failed to generate spiral matrix\n");
        return EXIT_FAILURE;
    }

    print_matrix(matrix, n);
    free_matrix(matrix, n);

    return EXIT_SUCCESS;
}