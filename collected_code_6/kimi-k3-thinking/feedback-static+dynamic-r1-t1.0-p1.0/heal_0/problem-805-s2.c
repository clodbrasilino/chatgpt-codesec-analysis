#include <stdio.h>
#include <stdlib.h>

static int sum_of_list(const int *list, size_t size)
{
    int sum = 0;
    size_t i;

    if (list == NULL)
    {
        return 0;
    }

    for (i = 0; i < size; i++)
    {
        sum += list[i];
    }

    return sum;
}

int find_highest_sum_list(int **lists, const size_t *sizes, size_t count)
{
    size_t i;
    size_t best_index;
    int best_sum;

    if (lists == NULL || sizes == NULL || count == 0)
    {
        return -1;
    }

    best_index = 0;
    best_sum = sum_of_list(lists[0], sizes[0]);

    for (i = 1; i < count; i++)
    {
        int current_sum = sum_of_list(lists[i], sizes[i]);

        if (current_sum > best_sum)
        {
            best_sum = current_sum;
            best_index = i;
        }
    }

    return (int)best_index;
}

int main(void)
{
    const size_t count = 4;
    const size_t sizes[4] = {3, 4, 2, 5};
    const int data[4][5] = {
        {1, 2, 3, 0, 0},
        {4, 5, 6, 7, 0},
        {10, 20, 0, 0, 0},
        {1, 1, 1, 1, 1}
    };
    int **lists = NULL;
    size_t i;
    size_t j;
    int result;

    lists = malloc(count * sizeof(*lists));
    if (lists == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++)
    {
        lists[i] = NULL;
    }

    for (i = 0; i < count; i++)
    {
        lists[i] = malloc(sizes[i] * sizeof(*lists[i]));
        if (lists[i] == NULL)
        {
            fprintf(stderr, "Error: memory allocation failed\n");
            for (j = 0; j < count; j++)
            {
                free(lists[j]);
            }
            free(lists);
            return EXIT_FAILURE;
        }
        for (j = 0; j < sizes[i]; j++)
        {
            lists[i][j] = data[i][j];
        }
    }

    result = find_highest_sum_list(lists, sizes, count);
    if (result < 0)
    {
        fprintf(stderr, "Error: invalid input\n");
    }
    else
    {
        printf("Index of list with highest sum: %d\n", result);
        printf("Elements:");
        for (i = 0; i < sizes[result]; i++)
        {
            printf(" %d", lists[result][i]);
        }
        printf("\nSum: %d\n", sum_of_list(lists[result], sizes[result]));
    }

    for (i = 0; i < count; i++)
    {
        free(lists[i]);
    }
    free(lists);
    lists = NULL;

    return EXIT_SUCCESS;
}