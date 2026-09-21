#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *concatenate_strings(const char **strings, size_t count)
{
    size_t total_length;
    size_t offset;
    size_t length;
    size_t i;
    char *result;

    if (strings == NULL || count == 0U || count >= (SIZE_MAX - 1U))
    {
        return NULL;
    }

    total_length = 0U;
    for (i = 0U; i < count; i++)
    {
        if (strings[i] == NULL)
        {
            return NULL;
        }
        length = strnlen(strings[i], SIZE_MAX - 1U);
        if (total_length > (SIZE_MAX - 1U) - length)
        {
            return NULL;
        }
        total_length += length;
    }

    result = malloc(total_length + 1U);
    if (result == NULL)
    {
        return NULL;
    }

    offset = 0U;
    for (i = 0U; i < count; i++)
    {
        length = strnlen(strings[i], total_length - offset);
        memcpy(result + offset, strings[i], length);
        offset += length;
    }
    result[offset] = '\0';

    return result;
}

int main(void)
{
    const char *strings[] = { "Hello", ", ", "World", "!" };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    char *joined;

    joined = concatenate_strings(strings, count);
    if (joined == NULL)
    {
        fprintf(stderr, "Failed to concatenate strings\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);
    free(joined);

    return EXIT_SUCCESS;
}