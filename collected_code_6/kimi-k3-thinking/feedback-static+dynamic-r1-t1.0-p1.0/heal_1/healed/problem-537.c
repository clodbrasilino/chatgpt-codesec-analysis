#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char *first_repeated_word(const char *str)
{
    char **seen = NULL;
    size_t *seen_len = NULL;
    size_t count = 0;
    size_t capacity = 0;
    char *result = NULL;
    const char *p = NULL;

    if (str == NULL)
    {
        return NULL;
    }

    p = str;

    while (*p != '\0')
    {
        const char *start = NULL;
        size_t len = 0;
        size_t i = 0;
        int found = 0;

        while (*p != '\0' && !isalnum((unsigned char)*p))
        {
            p++;
        }

        if (*p == '\0')
        {
            break;
        }

        start = p;

        while (*p != '\0' && isalnum((unsigned char)*p))
        {
            p++;
        }

        len = (size_t)(p - start);

        for (i = 0; i < count; i++)
        {
            if (seen_len[i] == len && memcmp(seen[i], start, len) == 0)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            result = (char *)malloc(len + 1u);
            if (result != NULL)
            {
                memcpy(result, start, len);
                result[len] = '\0';
            }
            break;
        }

        if (count == capacity)
        {
            size_t new_capacity = (capacity == 0u) ? 8u : capacity * 2u;
            char **new_seen = NULL;
            size_t *new_seen_len = NULL;

            if (capacity != 0u && new_capacity <= capacity)
            {
                break;
            }

            if (new_capacity > SIZE_MAX / sizeof(*seen) ||
                new_capacity > SIZE_MAX / sizeof(*seen_len))
            {
                break;
            }

            new_seen = (char **)realloc(seen, new_capacity * sizeof(*seen));
            if (new_seen == NULL)
            {
                break;
            }
            seen = new_seen;

            new_seen_len = (size_t *)realloc(seen_len, new_capacity * sizeof(*seen_len));
            if (new_seen_len == NULL)
            {
                break;
            }
            seen_len = new_seen_len;

            capacity = new_capacity;
        }

        if (len + 1u == 0u)
        {
            break;
        }

        seen[count] = (char *)malloc(len + 1u);
        if (seen[count] == NULL)
        {
            break;
        }

        memcpy(seen[count], start, len);
        seen[count][len] = '\0';
        seen_len[count] = len;
        count++;
    }

    {
        size_t i = 0;
        for (i = 0; i < count; i++)
        {
            free(seen[i]);
            seen[i] = NULL;
        }
    }

    free(seen);
    seen = NULL;
    free(seen_len);
    seen_len = NULL;

    return result;
}

static char *read_all_input(FILE *stream)
{
    size_t capacity = 256u;
    size_t length = 0u;
    char *buffer = NULL;
    int ch = 0;

    if (stream == NULL)
    {
        return NULL;
    }

    buffer = (char *)malloc(capacity);
    if (buffer == NULL)
    {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF)
    {
        if (length + 1u >= capacity)
        {
            size_t new_capacity = capacity * 2u;
            char *new_buffer = NULL;

            if (new_capacity <= capacity)
            {
                free(buffer);
                return NULL;
            }

            new_buffer = (char *)realloc(buffer, new_capacity);
            if (new_buffer == NULL)
            {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)ch;
        length++;
    }

    buffer[length] = '\0';

    return buffer;
}

int main(void)
{
    char *input = NULL;
    char *word = NULL;

    input = read_all_input(stdin);
    if (input == NULL)
    {
        printf("None\n");
        return EXIT_SUCCESS;
    }

    word = first_repeated_word(input);

    if (word != NULL)
    {
        printf("%s\n", word);
        free(word);
        word = NULL;
    }
    else
    {
        printf("None\n");
    }

    free(input);
    input = NULL;

    return EXIT_SUCCESS;
}