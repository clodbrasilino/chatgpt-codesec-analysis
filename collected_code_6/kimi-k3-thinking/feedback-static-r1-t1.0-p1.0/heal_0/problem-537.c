#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

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

int main(void)
{
    char input[4096];
    char *word = NULL;

    printf("Enter a string: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
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

    return EXIT_SUCCESS;
}