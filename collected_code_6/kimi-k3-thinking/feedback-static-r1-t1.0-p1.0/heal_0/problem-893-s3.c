#include <stdio.h>
#include <stdlib.h>

int *get_last_elements(int **sublists, const size_t *sizes, size_t count, size_t *result_size)
{
    int *result;
    size_t i;
    size_t valid_count;

    if (result_size == NULL)
    {
        return NULL;
    }
    *result_size = 0;

    if (sublists == NULL || sizes == NULL || count == 0)
    {
        return NULL;
    }

    valid_count = 0;
    for (i = 0; i < count; i++)
    {
        if (sublists[i] != NULL && sizes[i] > 0)
        {
            valid_count++;
        }
    }

    if (valid_count == 0)
    {
        return NULL;
    }

    result = (int *)malloc(valid_count * sizeof(int));
    if (result == NULL)
    {
        return NULL;
    }

    *result_size = valid_count;
    valid_count = 0;
    for (i = 0; i < count; i++)
    {
        if (sublists[i] != NULL && sizes[i] > 0)
        {
            result[valid_count] = sublists[i][sizes[i] - 1];
            valid_count++;
        }
    }

    return result;
}

int main(void)
{
    int **sublists;
    size_t *sizes;
    size_t count;
    size_t i;
    size_t j;
    int *last_elements;
    size_t result_size;
    int status;

    count = 4;
    status = EXIT_SUCCESS;

    sublists = (int **)malloc(count * sizeof(int *));
    if (sublists == NULL)
    {
        return EXIT_FAILURE;
    }

    sizes = (size_t *)malloc(count * sizeof(size_t));
    if (sizes == NULL)
    {
        free(sublists);
        return EXIT_FAILURE;
    }

    sizes[0] = 3;
    sizes[1] = 2;
    sizes[2] = 4;
    sizes[3] = 1;

    for (i = 0; i < count; i++)
    {
        sublists[i] = (int *)malloc(sizes[i] * sizeof(int));
        if (sublists[i] == NULL)
        {
            for (j = 0; j < i; j++)
            {
                free(sublists[j]);
            }
            free(sublists);
            free(sizes);
            return EXIT_FAILURE;
        }
    }

    sublists[0][0] = 1;
    sublists[0][1] = 2;
    sublists[0][2] = 3;
    sublists[1][0] = 4;
    sublists[1][1] = 5;
    sublists[2][0] = 6;
    sublists[2][1] = 7;
    sublists[2][2] = 8;
    sublists[2][3] = 9;
    sublists[3][0] = 10;

    last_elements = get_last_elements(sublists, sizes, count, &result_size);
    if (last_elements == NULL)
    {
        status = EXIT_FAILURE;
    }
    else
    {
        for (i = 0; i < result_size; i++)
        {
            printf("%d ", last_elements[i]);
        }
        printf("\n");
        free(last_elements);
    }

    for (i = 0; i < count; i++)
    {
        free(sublists[i]);
    }
    free(sublists);
    free(sizes);

    return status;
}