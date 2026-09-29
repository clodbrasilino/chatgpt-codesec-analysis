#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

char **split_at_uppercase(const char *str, int *count)
{
    int i, j, k = 0, start = 0;
    size_t len;
    char **result;

    if (str == NULL || count == NULL)
    {
        return NULL;
    }

    len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX)
    {
        *count = 0;
        return NULL;
    }

    if (len == 0)
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
            if (size - 1 > 0)
            {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                if (size - 1 <= strlen(str + start))
                {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[k], str + start, size - 1);
                }
                else
                {
                    for (j = 0; j <= k; j++)
                    {
                        free(result[j]);
                    }
                    free(result);
                    *count = 0;
                    return NULL;
                }
            }
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
        if (size - 1 > 0)
        {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (size - 1 <= strlen(str + start))
            {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[k], str + start, size - 1);
            }
            else
            {
                for (j = 0; j <= k; j++)
                {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }
        }
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