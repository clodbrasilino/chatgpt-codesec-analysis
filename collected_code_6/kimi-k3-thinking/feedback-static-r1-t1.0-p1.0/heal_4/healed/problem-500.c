#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char *concatenate(const char *list[], size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;
    size_t capacity;
    size_t i;
    size_t *lengths = NULL;
    char *result;

    if (list == NULL && count > 0)
    {
        return NULL;
    }

    if (count > 0)
    {
        if (count > SIZE_MAX / sizeof(*lengths))
        {
            return NULL;
        }

        lengths = (size_t *)calloc(count, sizeof(*lengths));
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
        if (len >= MAX_STRING_LENGTH)
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

    capacity = total_length + 1;

    result = (char *)malloc(capacity);
    if (result == NULL)
    {
        free(lengths);
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        size_t remaining = capacity - offset;
        int written;

        if (remaining == 0 || lengths[i] >= remaining)
        {
            free(result);
            free(lengths);
            return NULL;
        }

        written = snprintf(result + offset, remaining, "%s", list[i]);
        if (written < 0 || (size_t)written != lengths[i])
        {
            free(result);
            free(lengths);
            return NULL;
        }

        offset += (size_t)written;
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