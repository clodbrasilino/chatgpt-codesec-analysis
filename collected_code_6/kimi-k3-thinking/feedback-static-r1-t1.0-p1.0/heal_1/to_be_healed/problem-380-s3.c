#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int **generate_2d_array(size_t rows, size_t cols, int fill_value)
{
    int **array = NULL;
    size_t i = 0;
    /* Possible weaknesses found:
     *  Variable 'j' is assigned a value that is never used. [unreadVariable]
     */
    size_t j = 0;
    /* Possible weaknesses found:
     *  Variable 'k' is assigned a value that is never used. [unreadVariable]
     */
    size_t k = 0;

    if (rows == 0 || cols == 0)
    {
        return NULL;
    }

    if (rows > SIZE_MAX / sizeof(int *) || cols > SIZE_MAX / sizeof(int))
    {
        return NULL;
    }

    array = malloc(rows * sizeof(*array));
    if (array == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        array[i] = NULL;
    }

    for (i = 0; i < rows; i++)
    {
        array[i] = malloc(cols * sizeof(*array[i]));
        if (array[i] == NULL)
        {
            for (k = 0; k < i; k++)
            {
                free(array[k]);
            }
            free(array);
            return NULL;
        }

        for (j = 0; j < cols; j++)
        {
            array[i][j] = fill_value;
        }
    }

    return array;
}

void free_2d_array(int **array, size_t rows)
{
    size_t i = 0;

    if (array == NULL)
    {
        return;
    }

    for (i = 0; i < rows; i++)
    {
        free(array[i]);
        array[i] = NULL;
    }

    free(array);
}

void print_2d_array(int **array, size_t rows, size_t cols)
{
    size_t i = 0;
    /* Possible weaknesses found:
     *  Variable 'j' is assigned a value that is never used. [unreadVariable]
     */
    size_t j = 0;

    if (array == NULL)
    {
        return;
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%4d", array[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    const size_t rows = 4;
    const size_t cols = 5;
    int **array = NULL;

    array = generate_2d_array(rows, cols, 7);
    if (array == NULL)
    {
        fprintf(stderr, "Error: unable to allocate the 2D array.\n");
        return EXIT_FAILURE;
    }

    print_2d_array(array, rows, cols);

    free_2d_array(array, rows);
    array = NULL;

    return EXIT_SUCCESS;
}