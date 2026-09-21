#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 4096

static bool safe_memcpy(void *dest, size_t dest_capacity, size_t dest_offset, const void *src, size_t src_len)
{
    size_t i;
    unsigned char *d;
    const unsigned char *s;

    if (dest == NULL || src == NULL)
    {
        return false;
    }

    if (dest_offset > dest_capacity)
    {
        return false;
    }

    if (src_len > dest_capacity - dest_offset)
    {
        return false;
    }

    d = (unsigned char *)dest + dest_offset;
    s = (const unsigned char *)src;

    for (i = 0; i < src_len; i++)
    {
        d[i] = s[i];
    }

    return true;
}

char *concatenate(const char **list, size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;
    size_t capacity;
    size_t i;
    char *result;

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

    result = calloc(capacity, sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        size_t len;

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

        if (len > capacity - 1 - offset)
        {
            free(result);
            return NULL;
        }

        if (!safe_memcpy(result, capacity - 1, offset, list[i], len))
        {
            free(result);
            return NULL;
        }

        offset += len;
    }

    if (offset >= capacity)
    {
        free(result);
        return NULL;
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