#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_WORD_LENGTH 1023

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

static int safe_copy_string(char *dest, size_t dest_size, const char *src, size_t src_length)
{
    if (dest == NULL || src == NULL)
    {
        return -1;
    }

    if (src_length >= dest_size || dest_size < src_length + 1)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_length);
    dest[src_length] = '\0';

    return 0;
}

char *most_frequent_word(const char *const words[], size_t count, size_t *occurrences)
{
    size_t i;
    size_t j;
    size_t max_count = 0;
    size_t current_count;
    size_t max_index = 0;
    size_t length;
    size_t buffer_size;
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
            if (words[j] != NULL && strncmp(words[i], words[j], MAX_WORD_LENGTH + 1) == 0)
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

    if (length == SIZE_MAX)
    {
        return NULL;
    }

    buffer_size = length + 1;
    result = malloc(buffer_size);
    if (result == NULL)
    {
        return NULL;
    }

    if (safe_copy_string(result, buffer_size, words[max_index], length) != 0)
    {
        free(result);
        result = NULL;
        return NULL;
    }

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
    size_t occurrences = 0;
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