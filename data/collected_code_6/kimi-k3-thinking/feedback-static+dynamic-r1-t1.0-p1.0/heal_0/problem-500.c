#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate(const char *list[], size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;
    size_t i;
    char *result;

    if (list == NULL && count > 0)
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

        len = strlen(list[i]);
        if (total_length > SIZE_MAX - len - 1)
        {
            return NULL;
        }
        total_length += len;
    }

    result = (char *)malloc(total_length + 1);
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        size_t len = strlen(list[i]);
        memcpy(result + offset, list[i], len);
        offset += len;
    }
    result[offset] = '\0';

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