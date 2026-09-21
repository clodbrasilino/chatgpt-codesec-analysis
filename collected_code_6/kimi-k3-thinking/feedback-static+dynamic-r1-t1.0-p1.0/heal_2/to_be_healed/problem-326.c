#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 1024

static size_t bounded_strlen(const char *s, size_t max_length)
{
    size_t length = 0;

    if (s == NULL)
    {
        return 0;
    }

    while (length < max_length && s[length] != '\0')
    {
        length++;
    }

    return length;
}

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
            if (words[j] != NULL && strncmp(words[i], words[j], MAX_WORD_LENGTH) == 0)
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

    length = bounded_strlen(words[max_index], MAX_WORD_LENGTH);

    result = malloc(length + 1);
    if (result == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, words[max_index], length);
    result[length] = '\0';

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