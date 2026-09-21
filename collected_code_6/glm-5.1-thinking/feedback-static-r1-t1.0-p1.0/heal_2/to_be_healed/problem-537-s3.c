#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *find_first_repeated_word(const char *str, size_t str_len)
{
    if (str == NULL)
    {
        return NULL;
    }

    size_t max_words = str_len / 2 + 2;
    if (max_words > SIZE_MAX / sizeof(char *))
    {
        return NULL;
    }

    char **seen = malloc(max_words * sizeof(char *));
    if (seen == NULL)
    {
        return NULL;
    }

    size_t seen_count = 0;
    char *result = NULL;
    size_t i = 0;

    while (i < str_len && str[i] != '\0')
    {
        while (i < str_len && str[i] != '\0' && !isalnum((unsigned char)str[i]))
        {
            i++;
        }
        
        if (i >= str_len || str[i] == '\0')
        {
            break;
        }

        size_t start = i;
        while (i < str_len && str[i] != '\0' && isalnum((unsigned char)str[i]))
        {
            i++;
        }
        size_t word_len = i - start;

        char *word = malloc(word_len + 1);
        if (word == NULL)
        {
            goto cleanup;
        }
        
        memmove(word, str + start, word_len);
        word[word_len] = '\0';

        int found = 0;
        for (size_t j = 0; j < seen_count; j++)
        {
            if (strcmp(seen[j], word) == 0)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            result = malloc(word_len + 1);
            if (result != NULL)
            {
                memmove(result, word, word_len + 1);
            }
            free(word);
            goto cleanup;
        }
        else
        {
            if (seen_count < max_words)
            {
                seen[seen_count++] = word;
            }
            else
            {
                free(word);
            }
        }
    }

cleanup:
    for (size_t j = 0; j < seen_count; j++)
    {
        free(seen[j]);
    }
    free(seen);

    return result;
}

int main(void)
{
    const char *text1 = "This is a test, this is only a test.";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *repeated = find_first_repeated_word(text1, strlen(text1));
    if (repeated != NULL)
    {
        printf("%s\n", repeated);
        free(repeated);
    }
    else
    {
        printf("No repeated word found.\n");
    }

    const char *text2 = "No repetition here";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    repeated = find_first_repeated_word(text2, strlen(text2));
    if (repeated != NULL)
    {
        printf("%s\n", repeated);
        free(repeated);
    }
    else
    {
        printf("No repeated word found.\n");
    }

    return 0;
}