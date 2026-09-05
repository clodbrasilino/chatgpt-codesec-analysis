#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void free_string_array(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL)
    {
        return;
    }

    for (i = 0U; i < count; i++)
    {
        free(strings[i]);
    }
    free(strings);
}

static char **concat_adjacent_elements(const char *const *elements, size_t count, size_t *out_count)
{
    char **result;
    size_t i;

    if (out_count == NULL)
    {
        return NULL;
    }
    *out_count = 0U;

    if (elements == NULL || count < 2U)
    {
        return NULL;
    }

    for (i = 0U; i < count; i++)
    {
        if (elements[i] == NULL)
        {
            return NULL;
        }
    }

    result = malloc((count - 1U) * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0U; i < count - 1U; i++)
    {
        size_t left_len = strlen(elements[i]);
        size_t right_len = strlen(elements[i + 1U]);

        if (left_len > SIZE_MAX - right_len - 1U)
        {
            free_string_array(result, i);
            return NULL;
        }

        result[i] = malloc(left_len + right_len + 1U);
        if (result[i] == NULL)
        {
            free_string_array(result, i);
            return NULL;
        }

        memcpy(result[i], elements[i], left_len);
        memcpy(result[i] + left_len, elements[i + 1U], right_len);
        result[i][left_len + right_len] = '\0';
    }

    *out_count = count - 1U;
    return result;
}

int main(void)
{
    const char *tuple[] = {"1", "2", "3", "4", "5"};
    const size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    char **result;
    size_t result_count = 0U;
    size_t i;

    result = concat_adjacent_elements(tuple, tuple_size, &result_count);
    if (result == NULL)
    {
        fprintf(stderr, "Error: failed to concatenate adjacent elements.\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < result_count; i++)
    {
        printf("%s\n", result[i]);
    }

    free_string_array(result, result_count);

    return EXIT_SUCCESS;
}