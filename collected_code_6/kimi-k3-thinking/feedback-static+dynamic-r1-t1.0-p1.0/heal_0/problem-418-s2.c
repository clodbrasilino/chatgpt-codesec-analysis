#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Sublist;

const Sublist *find_max_length_sublist(const Sublist *lists, size_t num_lists)
{
    const Sublist *max_list;
    size_t i;

    if (lists == NULL || num_lists == 0)
    {
        return NULL;
    }

    max_list = &lists[0];
    for (i = 1; i < num_lists; i++)
    {
        if (lists[i].length > max_list->length)
        {
            max_list = &lists[i];
        }
    }

    return max_list;
}

int main(void)
{
    const size_t num_lists = 4;
    const size_t lengths[4] = {3, 5, 2, 4};
    const int values[4][5] = {
        {1, 2, 3, 0, 0},
        {10, 20, 30, 40, 50},
        {7, 8, 0, 0, 0},
        {100, 200, 300, 400, 0}
    };
    Sublist *lists;
    const Sublist *max_list;
    size_t i;
    size_t j;

    lists = malloc(num_lists * sizeof(*lists));
    if (lists == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_lists; i++)
    {
        lists[i].length = lengths[i];
        lists[i].data = malloc(lengths[i] * sizeof(*lists[i].data));
        if (lists[i].data == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            for (j = 0; j < i; j++)
            {
                free(lists[j].data);
            }
            free(lists);
            return EXIT_FAILURE;
        }
        for (j = 0; j < lengths[i]; j++)
        {
            lists[i].data[j] = values[i][j];
        }
    }

    max_list = find_max_length_sublist(lists, num_lists);
    if (max_list != NULL)
    {
        printf("Sublist with maximum length has length %zu\n", max_list->length);
        printf("Elements:");
        for (i = 0; i < max_list->length; i++)
        {
            printf(" %d", max_list->data[i]);
        }
        printf("\n");
    }
    else
    {
        printf("No sublists available.\n");
    }

    for (i = 0; i < num_lists; i++)
    {
        free(lists[i].data);
        lists[i].data = NULL;
    }
    free(lists);
    lists = NULL;

    return EXIT_SUCCESS;
}