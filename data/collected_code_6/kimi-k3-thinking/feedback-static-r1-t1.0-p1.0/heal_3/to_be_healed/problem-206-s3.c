#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 65536U

static size_t bounded_length(const char *text, size_t max_length)
{
    size_t length;

    length = 0U;

    if (text == NULL)
    {
        return 0U;
    }

    while (length < max_length && text[length] != '\0')
    {
        length++;
    }

    return length;
}

static int checked_copy(char *destination, size_t destination_capacity, size_t destination_offset, const char *source, size_t source_length)
{
    if (destination == NULL || source == NULL)
    {
        return -1;
    }

    if (destination_offset > destination_capacity)
    {
        return -1;
    }

    if (source_length > destination_capacity - destination_offset)
    {
        return -1;
    }

    if (source_length > 0U)
    {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination + destination_offset, source, source_length);
    }

    return 0;
}

static char *concat_pair(const char *first, const char *second)
{
    size_t len_first;
    size_t len_second;
    size_t total_length;
    char *combined;

    if (first == NULL || second == NULL)
    {
        return NULL;
    }

    len_first = bounded_length(first, MAX_STRING_LENGTH);
    if (len_first >= MAX_STRING_LENGTH)
    {
        return NULL;
    }

    len_second = bounded_length(second, MAX_STRING_LENGTH);
    if (len_second >= MAX_STRING_LENGTH)
    {
        return NULL;
    }

    if (len_first > SIZE_MAX - len_second - 1U)
    {
        return NULL;
    }

    total_length = len_first + len_second + 1U;

    combined = malloc(total_length);
    if (combined == NULL)
    {
        return NULL;
    }

    if (checked_copy(combined, total_length, 0U, first, len_first) != 0)
    {
        free(combined);
        return NULL;
    }

    if (checked_copy(combined, total_length, len_first, second, len_second) != 0)
    {
        free(combined);
        return NULL;
    }

    combined[total_length - 1U] = '\0';

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