#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

static size_t count_sublists_containing(const int *const *sublists,
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

static void cleanup(int **sublists, size_t sublist_count, size_t *lengths)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'j' can be reduced. [variableScope]
     */
    size_t j;

    if (sublists != NULL)
    {
        for (j = 0U; j < sublist_count; j++)
        {
            free(sublists[j]);
        }
        free(sublists);
    }

    free(lengths);
}

int main(void)
{
    const size_t sublist_count = 4U;
    const size_t template_lengths[4] = {3U, 2U, 4U, 1U};
    const int template_values[4][4] = {
        {1, 2, 3, 0},
        {4, 5, 0, 0},
        {2, 7, 8, 9},
        {10, 0, 0, 0}
    };
    const size_t template_row_count = sizeof(template_values) / sizeof(template_values[0]);
    const size_t template_row_size = sizeof(template_values[0]) / sizeof(template_values[0][0]);
    const size_t template_row_bytes = sizeof(template_values[0]);
    int **sublists = NULL;
    size_t *lengths = NULL;
    size_t i;
    size_t result;
    const int target = 2;

    if (sublist_count == 0U ||
        sublist_count > template_row_count ||
        sublist_count > (SIZE_MAX / sizeof(*sublists)))
    {
        fprintf(stderr, "Invalid sublist count\n");
        return EXIT_FAILURE;
    }

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
    }

    for (i = 0U; i < sublist_count; i++)
    {
        lengths[i] = template_lengths[i];

        if (lengths[i] == 0U ||
            lengths[i] > template_row_size ||
            lengths[i] > (SIZE_MAX / sizeof(*sublists[i])))
        {
            fprintf(stderr, "Invalid sublist length\n");
            cleanup(sublists, sublist_count, lengths);
            return EXIT_FAILURE;
        }

        {
            const size_t copy_size = lengths[i] * sizeof(*sublists[i]);
            /* Possible weaknesses found:
             *  'dest_capacity' is assigned value 'copy_size' here.
             */
            const size_t dest_capacity = copy_size;

            if (copy_size > template_row_bytes)
            {
                fprintf(stderr, "Copy size exceeds source buffer\n");
                cleanup(sublists, sublist_count, lengths);
                return EXIT_FAILURE;
            }

            sublists[i] = malloc(dest_capacity);
            if (sublists[i] == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                cleanup(sublists, sublist_count, lengths);
                return EXIT_FAILURE;
            }

            /* Possible weaknesses found:
             *  The comparison 'copy_size > dest_capacity' is always false because 'copy_size' and 'dest_capacity' represent the same value.
             *  The comparison 'copy_size > dest_capacity' is always false because 'copy_size' and 'dest_capacity' represent the same value. [knownConditionTrueFalse]
             */
            if (copy_size > dest_capacity)
            {
                fprintf(stderr, "Destination buffer too small for copy\n");
                cleanup(sublists, sublist_count, lengths);
                return EXIT_FAILURE;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(sublists[i], template_values[i], copy_size);
        }
    }

    result = count_sublists_containing((const int *const *)sublists,
                                       lengths,
                                       sublist_count,
                                       target);

    printf("Number of sublists containing %d: %zu\n", target, result);

    cleanup(sublists, sublist_count, lengths);

    return EXIT_SUCCESS;
}