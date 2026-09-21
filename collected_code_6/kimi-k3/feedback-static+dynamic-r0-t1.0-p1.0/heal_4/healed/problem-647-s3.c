#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **split_at_uppercase(const char *str, int *count)
{
    int i, j, k = 0, start = 0;
    size_t len = strnlen(str, SIZE_MAX);
    char **result = calloc(len + 1, sizeof(char *));
    if (result == NULL)
    {
        *count = 0;
        return NULL;
    }

    for (i = 0; i < (int)len; i++)
    {
        if (isupper((unsigned char)str[i]) && i != start)
        {
            size_t size = (size_t)(i - start) + 1;
            result[k] = malloc(size);
            if (result[k] == NULL)
            {
                for (j = 0; j < k; j++)
                {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }
            memcpy(result[k], str + start, size - 1);
            result[k][size - 1] = '\0';
            k++;
            start = i;
        }
    }

    if (start < (int)len)
    {
        size_t size = len - (size_t)start + 1;
        result[k] = malloc(size);
        if (result[k] == NULL)
        {
            for (j = 0; j < k; j++)
            {
                free(result[j]);
            }
            free(result);
            *count = 0;
            return NULL;
        }
        memcpy(result[k], str + start, size - 1);
        result[k][size - 1] = '\0';
        k++;
    }

    *count = k;
    return result;
}

int main(void)
{
    const char *input = "HelloWorldThisIsATest";
    int count = 0;
    char **parts = split_at_uppercase(input, &count);

    if (parts == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++)
    {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);

    return EXIT_SUCCESS;
}