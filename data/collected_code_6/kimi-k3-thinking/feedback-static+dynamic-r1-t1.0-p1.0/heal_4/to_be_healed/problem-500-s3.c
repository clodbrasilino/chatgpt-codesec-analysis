#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static size_t safe_strlen(const char *s, size_t maxlen)
{
    size_t len = 0;

    if (s == NULL)
    {
        return 0;
    }

    while (len < maxlen && s[len] != '\0')
    {
        len++;
    }

    return len;
}

char *concatenate(const char **list, size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;
    size_t i;
    size_t *lengths;
    char *result;

    if (list == NULL || count == 0)
    {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*lengths))
    {
        return NULL;
    }

    lengths = malloc(count * sizeof(*lengths));
    if (lengths == NULL)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        size_t len;

        if (list[i] == NULL)
        {
            free(lengths);
            return NULL;
        }

        len = safe_strlen(list[i], MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH)
        {
            free(lengths);
            return NULL;
        }

        if (len > SIZE_MAX - 1 - total_length)
        {
            free(lengths);
            return NULL;
        }

        lengths[i] = len;
        total_length += len;
    }

    result = malloc(total_length + 1);
    if (result == NULL)
    {
        free(lengths);
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        if (lengths[i] > 0)
        {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, list[i], lengths[i]);
            offset += lengths[i];
        }
    }

    result[offset] = '\0';

    free(lengths);
    lengths = NULL;

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