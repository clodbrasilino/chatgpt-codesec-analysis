#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *str, int *count)
{
    int i, j, k = 0, start = 0;
    int len = strlen(str);
    char **result = malloc(len * sizeof(char *));
    if (result == NULL)
    {
        *count = 0;
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
        if (isupper(str[i]) && i != start)
        {
            int size = i - start + 1;
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
            strncpy(result[k], str + start, i - start);
            result[k][i - start] = '\0';
            k++;
            start = i;
        }
    }

    if (start < len)
    {
        int size = len - start + 1;
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
        strncpy(result[k], str + start, len - start);
        result[k][len - start] = '\0';
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