#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char *concatenate(const char **list, size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;
    size_t capacity = 0;
    size_t i;
    char *result = NULL;

    if (list == NULL || count == 0)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        size_t len;

        if (list[i] == NULL)
        {
            return NULL;
        }

        len = strnlen(list[i], MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH)
        {
            return NULL;
        }

        if (len > SIZE_MAX - 1 - total_length)
        {
            return NULL;
        }
        total_length += len;
    }

    capacity = total_length + 1;

    result = malloc(capacity);
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        size_t len;
        size_t remaining;

        if (list[i] == NULL)
        {
            free(result);
            return NULL;
        }

        len = strnlen(list[i], MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH)
        {
            free(result);
            return NULL;
        }

        remaining = capacity - offset;
        if (len >= remaining)
        {
            free(result);
            return NULL;
        }

        if (len > 0)
        {
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }

    result[offset] = '\0';

    return result;
}

int main(void)
{
    const char *list[] = {"Hello", ", ", "World", "!"};
    size_t count = sizeof(list) / sizeof(list[0]);
    char *result = concatenate(list, count);

    if (result == NULL)
    {
        fprintf(stderr, "Error: failed to concatenate strings\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}