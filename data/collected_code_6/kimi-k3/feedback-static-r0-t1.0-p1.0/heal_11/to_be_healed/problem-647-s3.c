#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

char **split_at_uppercase(const char *str, int *count)
{
    int i, k = 0, start = 0;
    size_t len = 0;
    char **result = NULL;

    if (str == NULL || count == NULL)
    {
        if (count != NULL)
        {
            *count = 0;
        }
        return NULL;
    }

    len = strnlen(str, 4096);
    if (len == 4096 && str[4095] != '\0')
    {
        *count = 0;
        return NULL;
    }

    if (len > (size_t)(SIZE_MAX / sizeof(char *)) - 1)
    {
        *count = 0;
        return NULL;
    }

    result = calloc(len + 1, sizeof(char *));
    if (result == NULL)
    {
        *count = 0;
        return NULL;
    }

    for (i = 0; i < (int)len; i++)
    {
        if (isupper((unsigned char)str[i]) && i != start)
        {
            size_t substr_len = (size_t)(i - start);
            size_t size = substr_len + 1;

            if (substr_len >= len - (size_t)start)
            {
                for (int j = 0; j < k; j++)
                {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }

            result[k] = malloc(size);
            if (result[k] == NULL)
            {
                for (int j = 0; j < k; j++)
                {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }

            if (substr_len > 0)
            {
                if (substr_len >= size)
                {
                    for (int j = 0; j <= k; j++)
                    {
                        free(result[j]);
                    }
                    free(result);
                    *count = 0;
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[k], str + start, substr_len);
            }
            result[k][substr_len] = '\0';
            k++;
            start = i;
        }
    }

    if (start < (int)len)
    {
        size_t substr_len = len - (size_t)start;
        /* Possible weaknesses found:
         *  size is assigned 'substr_len+1' here.
         */
        size_t size = substr_len + 1;

        result[k] = malloc(size);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (result[k] == NULL)
        {
            for (int j = 0; j < k; j++)
            {
                free(result[j]);
            }
            free(result);
            *count = 0;
            return NULL;
        }

        if (substr_len > 0)
        {
            /* Possible weaknesses found:
             *  Condition 'substr_len>=size' is always false
             *  Condition 'substr_len>=size' is always false [knownConditionTrueFalse]
             */
            if (substr_len >= size)
            {
                for (int j = 0; j <= k; j++)
                {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[k], str + start, substr_len);
        }
        result[k][substr_len] = '\0';
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