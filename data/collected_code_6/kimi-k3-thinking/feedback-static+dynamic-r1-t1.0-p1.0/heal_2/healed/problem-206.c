#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 1048576U
#define INVALID_LENGTH ((size_t)-1)

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

static size_t safe_string_length(const char *s, size_t max_len)
{
    size_t len;

    if (s == NULL)
    {
        return INVALID_LENGTH;
    }

    for (len = 0U; len < max_len; len++)
    {
        if (s[len] == '\0')
        {
            return len;
        }
    }

    return INVALID_LENGTH;
}

static int checked_copy(char *dest, size_t dest_capacity, const char *src, size_t src_len)
{
    size_t i;

    if (dest == NULL || (src == NULL && src_len > 0U))
    {
        return -1;
    }

    if (dest_capacity < src_len)
    {
        return -1;
    }

    for (i = 0U; i < src_len; i++)
    {
        dest[i] = src[i];
    }

    return 0;
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

    if ((count - 1U) > (SIZE_MAX / sizeof(char *)))
    {
        return NULL;
    }

    for (i = 0U; i < count; i++)
    {
        if (elements[i] == NULL)
        {
            return NULL;
        }

        if (safe_string_length(elements[i], MAX_STRING_LENGTH) == INVALID_LENGTH)
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
        size_t left_len = safe_string_length(elements[i], MAX_STRING_LENGTH);
        size_t right_len = safe_string_length(elements[i + 1U], MAX_STRING_LENGTH);
        size_t total_len;

        if (left_len == INVALID_LENGTH || right_len == INVALID_LENGTH)
        {
            free_string_array(result, i);
            return NULL;
        }

        if (left_len > SIZE_MAX - right_len - 1U)
        {
            free_string_array(result, i);
            return NULL;
        }

        total_len = left_len + right_len;

        result[i] = malloc(total_len + 1U);
        if (result[i] == NULL)
        {
            free_string_array(result, i);
            return NULL;
        }

        if (checked_copy(result[i], total_len + 1U, elements[i], left_len) != 0)
        {
            free_string_array(result, i + 1U);
            return NULL;
        }

        if (checked_copy(result[i] + left_len, (total_len + 1U) - left_len, elements[i + 1U], right_len) != 0)
        {
            free_string_array(result, i + 1U);
            return NULL;
        }

        result[i][total_len] = '\0';
    }

    *out_count = count - 1U;
    return result;
}

int main(void)
{
    const char *tuple[] = {"DSP ", "IS ", "BEST ", "FOR ", "ALL ", "UTS"};
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