#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 4096

static size_t safe_strnlen(const char *s, size_t maxlen)
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

char **split_at_lowercase(const char *str, size_t *count)
{
    size_t n;
    size_t i;
    size_t tokens;
    size_t idx;
    char **result;

    if (str == NULL || count == NULL)
    {
        return NULL;
    }

    *count = 0;
    n = safe_strnlen(str, MAX_INPUT_LENGTH);
    tokens = 0;
    i = 0;

    while (i < n)
    {
        if (islower((unsigned char)str[i]))
        {
            i++;
        }
        else
        {
            tokens++;
            while (i < n && !islower((unsigned char)str[i]))
            {
                i++;
            }
        }
    }

    result = malloc((tokens + 1) * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    idx = 0;
    i = 0;

    while (i < n && idx < tokens)
    {
        if (islower((unsigned char)str[i]))
        {
            i++;
        }
        else
        {
            size_t start = i;
            size_t len;
            size_t bufsize;
            int written;

            while (i < n && !islower((unsigned char)str[i]))
            {
                i++;
            }
            len = i - start;
            bufsize = len + 1;

            result[idx] = malloc(bufsize);
            if (result[idx] == NULL)
            {
                size_t j;
                for (j = 0; j < idx; j++)
                {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            written = snprintf(result[idx], bufsize, "%.*s", (int)len, str + start);
            if (written < 0 || (size_t)written >= bufsize)
            {
                size_t j;
                free(result[idx]);
                for (j = 0; j < idx; j++)
                {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            idx++;
        }
    }

    result[idx] = NULL;
    *count = idx;
    return result;
}

void free_split(char **tokens, size_t count)
{
    size_t i;

    if (tokens == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        free(tokens[i]);
    }
    free(tokens);
}

int main(void)
{
    const char *input = "ABCdefGHIjklMNO";
    size_t count = 0;
    size_t i;
    char **tokens = split_at_lowercase(input, &count);

    if (tokens == NULL)
    {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++)
    {
        printf("Token %zu: %s\n", i, tokens[i]);
    }

    free_split(tokens, count);
    return EXIT_SUCCESS;
}