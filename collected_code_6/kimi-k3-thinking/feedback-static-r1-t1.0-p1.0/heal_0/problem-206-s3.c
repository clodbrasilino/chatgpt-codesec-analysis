#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *concat_pair(const char *first, const char *second)
{
    size_t len_first;
    size_t len_second;
    char *combined;

    if (first == NULL || second == NULL)
    {
        return NULL;
    }

    len_first = strlen(first);
    len_second = strlen(second);

    if (len_first > SIZE_MAX - len_second - 1U)
    {
        return NULL;
    }

    combined = malloc(len_first + len_second + 1U);
    if (combined == NULL)
    {
        return NULL;
    }

    memcpy(combined, first, len_first);
    memcpy(combined + len_first, second, len_second + 1U);

    return combined;
}

char **adjacent_concat(const char *tuple[], size_t count, size_t *out_count)
{
    char **result;
    size_t i;
    size_t j;

    if (out_count == NULL)
    {
        return NULL;
    }

    *out_count = 0U;

    if (tuple == NULL || count < 2U)
    {
        return NULL;
    }

    if (count - 1U > SIZE_MAX / sizeof(*result))
    {
        return NULL;
    }

    result = malloc((count - 1U) * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0U; i < count - 1U; i++)
    {
        result[i] = concat_pair(tuple[i], tuple[i + 1U]);
        if (result[i] == NULL)
        {
            for (j = 0U; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    *out_count = count - 1U;
    return result;
}

void free_adjacent_result(char *result[], size_t count)
{
    size_t i;

    if (result == NULL)
    {
        return;
    }

    for (i = 0U; i < count; i++)
    {
        free(result[i]);
    }

    free(result);
}

int main(void)
{
    const char *tuple[] = {"alpha", "beta", "gamma", "delta"};
    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    char **result;
    size_t result_count = 0U;
    size_t i;

    result = adjacent_concat(tuple, tuple_count, &result_count);
    if (result == NULL)
    {
        fprintf(stderr, "Failed to perform adjacent concatenation.\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < result_count; i++)
    {
        if (printf("%s\n", result[i]) < 0)
        {
            free_adjacent_result(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free_adjacent_result(result, result_count);

    return EXIT_SUCCESS;
}