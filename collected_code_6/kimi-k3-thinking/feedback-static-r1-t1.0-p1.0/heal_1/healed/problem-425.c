#include <stdio.h>
#include <stdlib.h>

#define SUBLIST_COUNT 4U
#define TEMPLATE_WIDTH 4U

static int list_contains(const int *list, size_t length, int target)
{
    size_t i;

    if (list == NULL)
    {
        return 0;
    }

    for (i = 0U; i < length; i++)
    {
        if (list[i] == target)
        {
            return 1;
        }
    }

    return 0;
}

size_t count_sublists_containing(const int *const *sublists,
                                 const size_t *lengths,
                                 size_t sublist_count,
                                 int target)
{
    size_t i;
    size_t count = 0U;

    if (sublists == NULL || lengths == NULL)
    {
        return 0U;
    }

    for (i = 0U; i < sublist_count; i++)
    {
        if (list_contains(sublists[i], lengths[i], target) != 0)
        {
            count++;
        }
    }

    return count;
}

static int copy_sublist(int *destination,
                        size_t destination_capacity,
                        const int *source,
                        size_t source_length)
{
    size_t i;

    if (destination == NULL || source == NULL)
    {
        return -1;
    }

    if (source_length > destination_capacity)
    {
        return -1;
    }

    for (i = 0U; i < source_length; i++)
    {
        destination[i] = source[i];
    }

    return 0;
}

int main(void)
{
    const size_t sublist_count = SUBLIST_COUNT;
    const size_t template_lengths[SUBLIST_COUNT] = {3U, 2U, 4U, 1U};
    const int template_values[SUBLIST_COUNT][TEMPLATE_WIDTH] = {
        {1, 2, 3, 0},
        {4, 5, 0, 0},
        {2, 7, 8, 9},
        {10, 0, 0, 0}
    };
    int **sublists = NULL;
    size_t *lengths = NULL;
    size_t i;
    size_t j;
    size_t result;
    const int target = 2;

    sublists = malloc(sublist_count * sizeof(*sublists));
    if (sublists == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    lengths = malloc(sublist_count * sizeof(*lengths));
    if (lengths == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(sublists);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < sublist_count; i++)
    {
        sublists[i] = NULL;
        lengths[i] = 0U;
    }

    for (i = 0U; i < sublist_count; i++)
    {
        if (template_lengths[i] == 0U || template_lengths[i] > TEMPLATE_WIDTH)
        {
            fprintf(stderr, "Invalid sublist length\n");
            for (j = 0U; j < sublist_count; j++)
            {
                free(sublists[j]);
            }
            free(sublists);
            free(lengths);
            return EXIT_FAILURE;
        }

        lengths[i] = template_lengths[i];

        sublists[i] = malloc(lengths[i] * sizeof(*sublists[i]));
        if (sublists[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0U; j < sublist_count; j++)
            {
                free(sublists[j]);
            }
            free(sublists);
            free(lengths);
            return EXIT_FAILURE;
        }

        if (copy_sublist(sublists[i], lengths[i], template_values[i], lengths[i]) != 0)
        {
            fprintf(stderr, "Copy failed\n");
            for (j = 0U; j < sublist_count; j++)
            {
                free(sublists[j]);
            }
            free(sublists);
            free(lengths);
            return EXIT_FAILURE;
        }
    }

    result = count_sublists_containing((const int *const *)sublists,
                                       lengths,
                                       sublist_count,
                                       target);

    printf("Number of sublists containing %d: %zu\n", target, result);

    for (i = 0U; i < sublist_count; i++)
    {
        free(sublists[i]);
    }
    free(sublists);
    free(lengths);

    return EXIT_SUCCESS;
}