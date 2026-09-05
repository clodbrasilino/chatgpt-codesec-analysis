#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *most_frequent_word(const char *const words[], size_t count, size_t *occurrences)
{
    size_t i;
    size_t j;
    size_t max_count = 0;
    size_t current_count;
    size_t max_index = 0;
    size_t length;
    char *result;

    if (occurrences != NULL)
    {
        *occurrences = 0;
    }

    if (words == NULL || count == 0)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        if (words[i] == NULL)
        {
            continue;
        }
        current_count = 1;
        for (j = i + 1; j < count; j++)
        {
            if (words[j] != NULL && strcmp(words[i], words[j]) == 0)
            {
                current_count++;
            }
        }
        if (current_count > max_count)
        {
            max_count = current_count;
            max_index = i;
        }
    }

    if (max_count == 0)
    {
        return NULL;
    }

    length = strlen(words[max_index]) + 1;
    result = malloc(length);
    if (result == NULL)
    {
        return NULL;
    }
    memcpy(result, words[max_index], length);

    if (occurrences != NULL)
    {
        *occurrences = max_count;
    }

    return result;
}

int main(void)
{
    const char *words[] = {
        "apple", "banana", "apple", "orange",
        "banana", "apple", "grape", "banana"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t occurrences;
    char *result;

    result = most_frequent_word(words, count, &occurrences);
    if (result == NULL)
    {
        fprintf(stderr, "Error: failed to find the most frequent word\n");
        return EXIT_FAILURE;
    }

    printf("Most frequent word: \"%s\" (%zu occurrences)\n", result, occurrences);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}