#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

static char *read_all_stdin(void)
{
    size_t capacity = 4096;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL)
    {
        return NULL;
    }

    for (;;)
    {
        size_t available = capacity - length;
        size_t n;

        if (available == 0)
        {
            char *new_buffer;

            if (capacity > SIZE_MAX / 2u)
            {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, capacity * 2u);
            if (new_buffer == NULL)
            {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity *= 2u;
            available = capacity - length;
        }

        n = fread(buffer + length, 1, available, stdin);
        if (n == 0)
        {
            break;
        }

        length += n;
    }

    buffer[length] = '\0';
    return buffer;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *first_repeated_word(const char *str)
{
    char **seen = NULL;
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
            if (strlen(seen[i]) == len && strncmp(seen[i], start, len) == 0)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            result = malloc(len + 1);
            if (result != NULL)
            {
                memcpy(result, start, len);
                result[len] = '\0';
            }
            break;
        }

        if (count == capacity)
        {
            size_t new_capacity = (capacity == 0) ? 8u : capacity * 2u;
            char **new_seen = NULL;

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

        seen[count] = malloc(len + 1);
        if (seen[count] == NULL)
        {
            break;
        }

        memcpy(seen[count], start, len);
        seen[count][len] = '\0';
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

    return result;
}

int main(int argc, char *argv[])
{
    const char *text = NULL;
    char *input = NULL;
    char *word = NULL;

    if (argc > 1)
    {
        text = argv[1];
    }
    else
    {
        input = read_all_stdin();
        if (input == NULL || input[0] == '\0')
        {
            free(input);
            printf("None\n");
            return EXIT_SUCCESS;
        }
        text = input;
    }

    word = first_repeated_word(text);

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