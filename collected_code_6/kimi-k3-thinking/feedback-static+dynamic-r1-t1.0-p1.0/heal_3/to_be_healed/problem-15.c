#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 65536

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && str[len] != '\0')
    {
        len++;
    }

    return len;
}

static char **split_at_lowercase(const char *str, size_t *count)
{
    char **result = NULL;
    char **temp = NULL;
    char *part = NULL;
    size_t num_parts = 0;
    size_t capacity = 8;
    size_t len = 0;
    size_t i = 0;

    if (str == NULL || count == NULL)
    {
        return NULL;
    }

    *count = 0;
    len = bounded_length(str, MAX_STRING_LENGTH);

    result = malloc(capacity * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    while (i < len)
    {
        size_t start;
        size_t part_len;

        while (i < len && islower((unsigned char)str[i]))
        {
            i++;
        }
        /* Possible weaknesses found:
         *  Assuming that condition 'i>=len' is not redundant
         */
        if (i >= len)
        {
            break;
        }

        /* Possible weaknesses found:
         *  start is assigned 'i' here.
         */
        start = i;
        while (i < len && !islower((unsigned char)str[i]))
        {
            i++;
        }
        part_len = i - start;

        /* Possible weaknesses found:
         *  Condition 'start>=len' is always true
         *  Condition 'start>=len' is always true [knownConditionTrueFalse]
         */
        if (part_len == 0 || start >= len || part_len > len - start)
        {
            break;
        }

        if (num_parts >= capacity)
        {
            temp = realloc(result, capacity * 2 * sizeof(*result));
            if (temp == NULL)
            {
                size_t j;

                for (j = 0; j < num_parts; j++)
                {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            result = temp;
            capacity *= 2;
        }

        part = malloc(part_len + 1);
        if (part == NULL)
        {
            size_t j;

            for (j = 0; j < num_parts; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        {
            size_t k;

            for (k = 0; k < part_len && (start + k) < len; k++)
            {
                part[k] = str[start + k];
            }
        }
        part[part_len] = '\0';
        result[num_parts] = part;
        num_parts++;
    }

    *count = num_parts;
    return result;
}

static void free_split(char **parts, size_t count)
{
    size_t i = 0;

    if (parts == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        free(parts[i]);
    }
    free(parts);
}

int main(void)
{
    const char *input = "ABCdefGHIjklMNOpqrSTU";
    char **parts = NULL;
    size_t count = 0;
    size_t i = 0;

    parts = split_at_lowercase(input, &count);
    if (parts == NULL)
    {
        fprintf(stderr, "Error: failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++)
    {
        printf("Part %zu: %s\n", i, parts[i]);
    }

    free_split(parts, count);
    parts = NULL;

    return EXIT_SUCCESS;
}