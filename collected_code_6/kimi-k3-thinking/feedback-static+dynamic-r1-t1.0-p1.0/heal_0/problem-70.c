#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *data;
    size_t length;
} Tuple;

bool all_tuples_equal_length(const Tuple tuples[], size_t count)
{
    size_t i;

    if (tuples == NULL || count == 0U)
    {
        return false;
    }

    for (i = 1U; i < count; i++)
    {
        if (tuples[i].length != tuples[0U].length)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    Tuple tuples[3];
    size_t i;
    bool result;
    int status = EXIT_SUCCESS;

    for (i = 0U; i < 3U; i++)
    {
        tuples[i].data = NULL;
        tuples[i].length = 0U;
    }

    tuples[0].length = 3U;
    tuples[1].length = 3U;
    tuples[2].length = 3U;

    for (i = 0U; i < 3U; i++)
    {
        tuples[i].data = (int *)malloc(tuples[i].length * sizeof(int));
        if (tuples[i].data == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            status = EXIT_FAILURE;
            break;
        }
    }

    if (status == EXIT_SUCCESS)
    {
        result = all_tuples_equal_length(tuples, 3U);
        if (result)
        {
            printf("All tuples have equal length.\n");
        }
        else
        {
            printf("Not all tuples have equal length.\n");
        }
    }

    for (i = 0U; i < 3U; i++)
    {
        free(tuples[i].data);
        tuples[i].data = NULL;
    }

    return status;
}