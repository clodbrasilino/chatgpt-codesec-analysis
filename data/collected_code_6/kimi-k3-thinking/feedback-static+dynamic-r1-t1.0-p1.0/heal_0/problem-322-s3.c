#include <stdio.h>
#include <stdlib.h>

size_t find_min_indices(const int *list, size_t size, size_t **indices)
{
    size_t *result;
    size_t count;
    size_t i;
    int min_val;

    if (indices == NULL)
    {
        return 0;
    }

    *indices = NULL;

    if (list == NULL || size == 0)
    {
        return 0;
    }

    result = malloc(size * sizeof(*result));
    if (result == NULL)
    {
        return 0;
    }

    min_val = list[0];
    count = 0;

    for (i = 0; i < size; i++)
    {
        if (list[i] < min_val)
        {
            min_val = list[i];
            count = 0;
            result[count] = i;
            count++;
        }
        else if (list[i] == min_val)
        {
            result[count] = i;
            count++;
        }
    }

    *indices = result;
    return count;
}

int main(void)
{
    int list[] = {4, 2, 7, 2, 9, 2, 5};
    size_t size;
    size_t *indices;
    size_t count;
    size_t i;

    size = sizeof(list) / sizeof(list[0]);
    indices = NULL;

    count = find_min_indices(list, size, &indices);

    if (count == 0 || indices == NULL)
    {
        fprintf(stderr, "Error: unable to find minimum indices\n");
        free(indices);
        return EXIT_FAILURE;
    }

    printf("Minimum value: %d\n", list[indices[0]]);
    printf("Index positions: ");
    for (i = 0; i < count; i++)
    {
        printf("%zu", indices[i]);
        if (i + 1 < count)
        {
            printf(", ");
        }
    }
    printf("\n");

    free(indices);
    indices = NULL;

    return EXIT_SUCCESS;
}