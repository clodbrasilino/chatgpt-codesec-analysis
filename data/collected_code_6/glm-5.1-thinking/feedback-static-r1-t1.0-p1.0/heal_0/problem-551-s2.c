#include <stdio.h>
#include <stdlib.h>

int *extract_column(int **list, size_t rows, const size_t *row_sizes, size_t col_index, size_t *out_size)
{
    if (list == NULL || row_sizes == NULL || out_size == NULL)
    {
        if (out_size != NULL)
        {
            *out_size = 0;
        }
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < rows; i++)
    {
        if (list[i] != NULL && col_index < row_sizes[i])
        {
            count++;
        }
    }

    if (count == 0)
    {
        *out_size = 0;
        return NULL;
    }

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL)
    {
        *out_size = 0;
        return NULL;
    }

    size_t res_idx = 0;
    for (size_t i = 0; i < rows; i++)
    {
        if (list[i] != NULL && col_index < row_sizes[i])
        {
            result[res_idx] = list[i][col_index];
            res_idx++;
        }
    }

    *out_size = count;
    return result;
}

int main(void)
{
    size_t rows = 3;
    int **list = (int **)malloc(rows * sizeof(int *));
    size_t row_sizes[3] = {3, 2, 4};

    if (list == NULL)
    {
        return EXIT_FAILURE;
    }

    list[0] = (int *)malloc(row_sizes[0] * sizeof(int));
    if (list[0] == NULL)
    {
        free(list);
        return EXIT_FAILURE;
    }

    list[1] = (int *)malloc(row_sizes[1] * sizeof(int));
    if (list[1] == NULL)
    {
        free(list[0]);
        free(list);
        return EXIT_FAILURE;
    }

    list[2] = (int *)malloc(row_sizes[2] * sizeof(int));
    if (list[2] == NULL)
    {
        free(list[1]);
        free(list[0]);
        free(list);
        return EXIT_FAILURE;
    }

    list[0][0] = 1;
    list[0][1] = 2;
    list[0][2] = 3;

    list[1][0] = 4;
    list[1][1] = 5;

    list[2][0] = 7;
    list[2][1] = 8;
    list[2][2] = 9;
    list[2][3] = 10;

    size_t out_size = 0;
    size_t col_index = 1;

    int *column = extract_column(list, rows, row_sizes, col_index, &out_size);

    if (column != NULL)
    {
        for (size_t i = 0; i < out_size; i++)
        {
            printf("%d ", column[i]);
        }
        printf("\n");
        free(column);
    }

    for (size_t i = 0; i < rows; i++)
    {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}