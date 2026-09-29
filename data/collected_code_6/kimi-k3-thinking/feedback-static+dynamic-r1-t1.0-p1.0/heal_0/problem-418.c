#include <stdio.h>
#include <stdlib.h>

int find_max_length_sublist(int *const *lists, const size_t *lengths, size_t count, size_t *max_index)
{
    size_t i;

    if (lists == NULL || lengths == NULL || max_index == NULL || count == 0)
    {
        return -1;
    }

    *max_index = 0;

    for (i = 1; i < count; i++)
    {
        if (lengths[i] > lengths[*max_index])
        {
            *max_index = i;
        }
    }

    return 0;
}

int main(void)
{
    const size_t count = 4;
    const size_t lengths[4] = {2, 4, 3, 1};
    int **lists = NULL;
    size_t max_index = 0;
    size_t i;
    size_t j;
    int value = 1;
    int status = EXIT_FAILURE;

    lists = malloc(count * sizeof(*lists));
    if (lists == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++)
    {
        lists[i] = NULL;
    }

    for (i = 0; i < count; i++)
    {
        if (lengths[i] == 0)
        {
            continue;
        }
        lists[i] = malloc(lengths[i] * sizeof(*lists[i]));
        if (lists[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            goto cleanup;
        }
        for (j = 0; j < lengths[i]; j++)
        {
            lists[i][j] = value;
            value++;
        }
    }

    if (find_max_length_sublist(lists, lengths, count, &max_index) != 0)
    {
        fprintf(stderr, "Unable to determine the longest sublist\n");
        goto cleanup;
    }

    printf("Longest sublist -> index: %zu, length: %zu, elements: ", max_index, lengths[max_index]);
    for (j = 0; j < lengths[max_index]; j++)
    {
        printf("%d ", lists[max_index][j]);
    }
    printf("\n");

    status = EXIT_SUCCESS;

cleanup:
    for (i = 0; i < count; i++)
    {
        free(lists[i]);
    }
    free(lists);

    return status;
}