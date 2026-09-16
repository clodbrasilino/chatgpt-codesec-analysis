#include <stdio.h>
#include <stdlib.h>

int *find_max_sum_list(int **lists, size_t num_lists, const size_t *sizes, size_t *max_index)
{
    size_t i;
    size_t j;
    long sum;
    long max_sum = 0;
    size_t best_index = 0;
    int found = 0;

    if (lists == NULL || sizes == NULL || num_lists == 0 || max_index == NULL)
    {
        return NULL;
    }

    for (i = 0; i < num_lists; i++)
    {
        if (lists[i] == NULL || sizes[i] == 0)
        {
            continue;
        }
        sum = 0;
        for (j = 0; j < sizes[i]; j++)
        {
            sum += lists[i][j];
        }
        if (!found || sum > max_sum)
        {
            max_sum = sum;
            best_index = i;
            found = 1;
        }
    }

    if (!found)
    {
        return NULL;
    }

    *max_index = best_index;
    return lists[best_index];
}

int main(void)
{
    size_t num_lists = 3;
    int **lists = NULL;
    size_t *sizes = NULL;
    size_t i;
    size_t max_index = 0;
    int *result = NULL;

    lists = (int **)calloc(num_lists, sizeof(int *));
    if (lists == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    sizes = (size_t *)calloc(num_lists, sizeof(size_t));
    if (sizes == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        free(lists);
        return EXIT_FAILURE;
    }

    sizes[0] = 3;
    sizes[1] = 4;
    sizes[2] = 2;

    for (i = 0; i < num_lists; i++)
    {
        lists[i] = (int *)calloc(sizes[i], sizeof(int));
        if (lists[i] == NULL)
        {
            fprintf(stderr, "Allocation failed\n");
            while (i > 0)
            {
                i--;
                free(lists[i]);
                lists[i] = NULL;
            }
            free(sizes);
            free(lists);
            return EXIT_FAILURE;
        }
    }

    lists[0][0] = 1;
    lists[0][1] = 2;
    lists[0][2] = 3;

    lists[1][0] = 10;
    lists[1][1] = 20;
    lists[1][2] = 30;
    lists[1][3] = 40;

    lists[2][0] = 5;
    lists[2][1] = 6;

    result = find_max_sum_list(lists, num_lists, sizes, &max_index);

    if (result != NULL)
    {
        printf("List with highest sum (index %zu): ", max_index);
        for (size_t j = 0; j < sizes[max_index]; j++)
        {
            printf("%d ", result[j]);
        }
        printf("\n");
    }
    else
    {
        printf("No valid list found.\n");
    }

    for (i = 0; i < num_lists; i++)
    {
        free(lists[i]);
        lists[i] = NULL;
    }
    free(sizes);
    sizes = NULL;
    free(lists);
    lists = NULL;

    return EXIT_SUCCESS;
}