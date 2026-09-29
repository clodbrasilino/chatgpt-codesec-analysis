#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char *concatenate(const char *list[], size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;
    size_t i;
    char *result = NULL;
    size_t *lengths = NULL;

    if (list == NULL && count > 0)
    {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(size_t))
    {
        return NULL;
    }

    if (count > 0)
    {
        lengths = (size_t *)malloc(count * sizeof(size_t));
        if (lengths == NULL)
        {
            return NULL;
        }
    }

    for (i = 0; i < count; i++)
    {
        size_t len;

        if (list[i] == NULL)
        {
            free(lengths);
            return NULL;
        }

        len = strnlen(list[i], MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH)
        {
            free(lengths);
            return NULL;
        }

        if (total_length > SIZE_MAX - len - 1)
        {
            free(lengths);
            return NULL;
        }

        lengths[i] = len;
        total_length += len;
    }

    result = (char *)malloc(total_length + 1);
    if (result == NULL)
    {
        free(lengths);
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        size_t len = lengths[i];

        if (len > 0)
        {
            if (len > total_length - offset)
            {
                free(lengths);
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }

    result[offset] = '\0';
    free(lengths);

    return result;
}

int main(void)
{
    const char *list[] = {"Hello", " ", "World", "!"};
    size_t count = sizeof(list) / sizeof(list[0]);
    char *result = concatenate(list, count);

    if (result == NULL)
    {
        fprintf(stderr, "Error: concatenation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    free(result);

    return EXIT_SUCCESS;
}