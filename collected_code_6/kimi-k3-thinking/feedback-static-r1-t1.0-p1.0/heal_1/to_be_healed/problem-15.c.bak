#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char **split_at_lowercase(const char *str, size_t *count)
{
    char **result = NULL;
    char **temp = NULL;
    char *part = NULL;
    size_t num_parts = 0;
    size_t capacity = 8;
    size_t len = 0;
    size_t i = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     *  Variable 'start' is assigned a value that is never used. [unreadVariable]
     */
    size_t start = 0;
    /* Possible weaknesses found:
     *  Variable 'j' is assigned a value that is never used. [unreadVariable]
     */
    size_t j = 0;

    if (str == NULL || count == NULL)
    {
        return NULL;
    }

    *count = 0;
    len = strlen(str);

    result = malloc(capacity * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    while (i < len)
    {
        while (i < len && islower((unsigned char)str[i]))
        {
            i++;
        }
        if (i >= len)
        {
            break;
        }

        start = i;
        while (i < len && !islower((unsigned char)str[i]))
        {
            i++;
        }

        if (num_parts >= capacity)
        {
            temp = realloc(result, capacity * 2 * sizeof(*result));
            if (temp == NULL)
            {
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

        part = malloc(i - start + 1);
        if (part == NULL)
        {
            for (j = 0; j < num_parts; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        memcpy(part, str + start, i - start);
        part[i - start] = '\0';
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