#include <stdio.h>
#include <stdlib.h>

int *get_last_elements(int **sublists, const size_t *lengths, size_t count)
{
    int *result = NULL;
    size_t i;

    if (sublists == NULL || lengths == NULL || count == 0)
    {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        if (sublists[i] == NULL || lengths[i] == 0)
        {
            free(result);
            return NULL;
        }
        result[i] = sublists[i][lengths[i] - 1];
    }

    return result;
}

int main(void)
{
    int list1[] = {1, 2, 3};
    int list2[] = {10, 20};
    int list3[] = {7, 8, 9, 11};
    int *sublists[] = {list1, list2, list3};
    size_t lengths[] = {3, 2, 4};
    size_t count = sizeof(sublists) / sizeof(sublists[0]);
    int *last_elements = NULL;
    size_t i;

    last_elements = get_last_elements(sublists, lengths, count);
    if (last_elements == NULL)
    {
        fprintf(stderr, "Error: unable to retrieve last elements\n");
        return EXIT_FAILURE;
    }

    printf("Last elements: ");
    for (i = 0; i < count; i++)
    {
        printf("%d ", last_elements[i]);
    }
    printf("\n");

    free(last_elements);
    last_elements = NULL;

    return EXIT_SUCCESS;
}