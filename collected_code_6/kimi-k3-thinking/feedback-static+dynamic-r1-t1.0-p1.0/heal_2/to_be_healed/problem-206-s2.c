#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char **adjacent_concat(const char **tuple, size_t size, size_t *result_size)
{
    char **result;
    size_t i;

    if (tuple == NULL || result_size == NULL)
    {
        return NULL;
    }

    *result_size = 0;

    if (size < 2)
    {
        return NULL;
    }

    if (size - 1 > SIZE_MAX / sizeof(char *))
    {
        return NULL;
    }

    result = (char **)malloc((size - 1) * sizeof(char *));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < size - 1; i++)
    {
        size_t len1;
        size_t len2;
        size_t total;

        if (tuple[i] == NULL || tuple[i + 1] == NULL)
        {
            size_t j;
            for (j = 0; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        len1 = strnlen(tuple[i], MAX_STRING_LENGTH);
        len2 = strnlen(tuple[i + 1], MAX_STRING_LENGTH);

        if (len1 >= MAX_STRING_LENGTH || len2 >= MAX_STRING_LENGTH)
        {
            size_t j;
            for (j = 0; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        if (len1 > SIZE_MAX - len2 - 1)
        {
            size_t j;
            for (j = 0; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        total = len1 + len2 + 1;

        result[i] = (char *)malloc(total);
        if (result[i] == NULL)
        {
            size_t j;
            for (j = 0; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        if (len1 <= total && len2 + 1 <= total - len1)
        {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[i], tuple[i], len1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[i] + len1, tuple[i + 1], len2 + 1);
        }
        else
        {
            size_t j;
            free(result[i]);
            for (j = 0; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    *result_size = size - 1;
    return result;
}

void free_concat_result(char **result, size_t size)
{
    size_t i;

    if (result == NULL)
    {
        return;
    }

    for (i = 0; i < size; i++)
    {
        free(result[i]);
    }
    free(result);
}

int main(void)
{
    const char *tuple[] = {"1", "2", "3", "4", "5"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    size_t result_size = 0;
    char **result;
    size_t i;

    result = adjacent_concat(tuple, size, &result_size);
    if (result == NULL)
    {
        fprintf(stderr, "Error: adjacent concatenation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Input tuple: (");
    for (i = 0; i < size; i++)
    {
        printf("%s%s", tuple[i], (i + 1 < size) ? ", " : "");
    }
    printf(")\n");

    printf("Adjacent concatenation: (");
    for (i = 0; i < result_size; i++)
    {
        printf("%s%s", result[i], (i + 1 < result_size) ? ", " : "");
    }
    printf(")\n");

    free_concat_result(result, result_size);

    return EXIT_SUCCESS;
}