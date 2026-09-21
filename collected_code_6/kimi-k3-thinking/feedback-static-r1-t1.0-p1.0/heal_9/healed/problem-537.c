#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

struct word_entry
{
    char *text;
    size_t length;
};

static int copy_word(char *dest, size_t dest_size, const char *src, size_t src_len)
{
    size_t i = 0u;

    if (dest == NULL || src == NULL)
    {
        return -1;
    }

    if (dest_size == 0u || src_len >= dest_size)
    {
        return -1;
    }

    for (i = 0u; i < src_len; i++)
    {
        dest[i] = src[i];
    }

    dest[src_len] = '\0';

    return 0;
}

char *first_repeated_word(const char *str)
{
    struct word_entry *seen = NULL;
    size_t count = 0u;
    size_t capacity = 0u;
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
        size_t len = 0u;
        size_t i = 0u;
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

        for (i = 0u; i < count; i++)
        {
            if (seen[i].length == len && memcmp(seen[i].text, start, len) == 0)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            if (len == SIZE_MAX)
            {
                break;
            }

            result = malloc(len + 1u);
            if (result != NULL)
            {
                if (copy_word(result, len + 1u, start, len) != 0)
                {
                    free(result);
                    result = NULL;
                }
            }
            break;
        }

        if (count == capacity)
        {
            size_t new_capacity = 0u;
            struct word_entry *new_seen = NULL;

            if (capacity > SIZE_MAX / 2u)
            {
                break;
            }

            new_capacity = (capacity == 0u) ? 8u : capacity * 2u;

            if (new_capacity > SIZE_MAX / sizeof(*seen))
            {
                break;
            }

            new_seen = realloc(seen, new_capacity * sizeof(*seen));
            if (new_seen == NULL)
            {
                break;
            }

            seen = new_seen;
            capacity = new_capacity;
        }

        if (len == SIZE_MAX)
        {
            break;
        }

        seen[count].text = malloc(len + 1u);
        if (seen[count].text == NULL)
        {
            break;
        }

        if (copy_word(seen[count].text, len + 1u, start, len) != 0)
        {
            free(seen[count].text);
            seen[count].text = NULL;
            break;
        }

        seen[count].length = len;
        count++;
    }

    {
        size_t i = 0u;

        for (i = 0u; i < count; i++)
        {
            free(seen[i].text);
            seen[i].text = NULL;
        }
    }

    free(seen);
    seen = NULL;

    return result;
}

static char *read_input(FILE *stream)
{
    size_t capacity = 128u;
    size_t length = 0u;
    char *buffer = NULL;
    int ch = 0;

    if (stream == NULL)
    {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL)
    {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n')
    {
        if (length + 1u >= capacity)
        {
            size_t new_capacity = 0u;
            char *new_buffer = NULL;

            if (capacity > SIZE_MAX / 2u)
            {
                free(buffer);
                buffer = NULL;
                return NULL;
            }

            new_capacity = capacity * 2u;

            if (new_capacity <= capacity)
            {
                free(buffer);
                buffer = NULL;
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL)
            {
                free(buffer);
                buffer = NULL;
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        if (length < capacity && length + 1u < capacity)
        {
            buffer[length] = (char)(unsigned char)ch;
            length++;
        }
        else
        {
            free(buffer);
            buffer = NULL;
            return NULL;
        }
    }

    if (ferror(stream))
    {
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    if (ch == EOF && length == 0u)
    {
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    if (length >= capacity)
    {
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    buffer[length] = '\0';

    return buffer;
}

int main(void)
{
    char *input = NULL;
    char *word = NULL;

    printf("Enter a string: ");
    fflush(stdout);

    input = read_input(stdin);
    if (input == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    word = first_repeated_word(input);

    if (word != NULL)
    {
        printf("First repeated word: %s\n", word);
        free(word);
        word = NULL;
    }
    else
    {
        printf("No repeated word found.\n");
    }

    free(input);
    input = NULL;

    return EXIT_SUCCESS;
}