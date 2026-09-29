#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} Sublist;

size_t max_sublist_length(const Sublist *sublists, size_t count)
{
    size_t max_length = 0;
    size_t i;

    if (sublists == NULL)
    {
        return 0;
    }

    for (i = 0; i < count; i++)
    {
        if (sublists[i].length > max_length)
        {
            max_length = sublists[i].length;
        }
    }

    return max_length;
}

void free_sublists(Sublist *sublists, size_t count)
{
    size_t i;

    if (sublists == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        free(sublists[i].data);
        sublists[i].data = NULL;
    }

    free(sublists);
}

int main(void)
{
    const size_t sizes[] = {3, 7, 2, 5, 1};
    const size_t count = sizeof(sizes) / sizeof(sizes[0]);
    Sublist *sublists;
    size_t max_length;
    size_t i;
    size_t j;

    sublists = malloc(count * sizeof(*sublists));
    if (sublists == NULL)
    {
        fprintf(stderr, "Error: failed to allocate sublist array\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++)
    {
        sublists[i].data = NULL;
        sublists[i].length = 0;
    }

    for (i = 0; i < count; i++)
    {
        sublists[i].data = malloc(sizes[i] * sizeof(*sublists[i].data));
        if (sublists[i].data == NULL)
        {
            fprintf(stderr, "Error: failed to allocate sublist %zu\n", i);
            free_sublists(sublists, count);
            return EXIT_FAILURE;
        }

        sublists[i].length = sizes[i];
        for (j = 0; j < sizes[i]; j++)
        {
            sublists[i].data[j] = (int)(i * 10 + j);
        }
    }

    max_length = max_sublist_length(sublists, count);
    printf("Maximum sublist length: %zu\n", max_length);

    free_sublists(sublists, count);
    sublists = NULL;

    return EXIT_SUCCESS;
}