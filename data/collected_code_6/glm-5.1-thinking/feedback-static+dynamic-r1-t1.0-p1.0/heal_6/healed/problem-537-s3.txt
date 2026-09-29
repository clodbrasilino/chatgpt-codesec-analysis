#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_first_repeated_word(const char *str)
{
    if (str == NULL)
    {
        char *none_str = malloc(5);
        if (none_str != NULL)
        {
            snprintf(none_str, 5, "%s", "None");
        }
        return none_str;
    }

    size_t seen_capacity = 16;
    char **seen = malloc(seen_capacity * sizeof(char *));
    if (seen == NULL)
    {
        char *none_str = malloc(5);
        if (none_str != NULL)
        {
            snprintf(none_str, 5, "%s", "None");
        }
        return none_str;
    }

    size_t seen_count = 0;
    char *result = NULL;
    size_t i = 0;

    while (str[i] != '\0')
    {
        while (str[i] != '\0' && !isalnum((unsigned char)str[i]))
        {
            i++;
        }
        
        if (str[i] == '\0')
        {
            break;
        }

        size_t start = i;
        while (str[i] != '\0' && isalnum((unsigned char)str[i]))
        {
            i++;
        }
        size_t word_len = i - start;

        char *word = malloc(word_len + 1);
        if (word == NULL)
        {
            goto cleanup;
        }
        
        memcpy(word, str + start, word_len);
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
                memcpy(result, word, word_len + 1);
            }
            free(word);
            goto cleanup;
        }
        else
        {
            if (seen_count == seen_capacity)
            {
                size_t new_capacity = seen_capacity * 2;
                if (new_capacity / 2 != seen_capacity)
                {
                    free(word);
                    goto cleanup;
                }
                seen_capacity = new_capacity;
                char **new_seen = realloc(seen, seen_capacity * sizeof(char *));
                if (new_seen == NULL)
                {
                    free(word);
                    goto cleanup;
                }
                seen = new_seen;
            }
            seen[seen_count++] = word;
        }
    }

cleanup:
    for (size_t j = 0; j < seen_count; j++)
    {
        free(seen[j]);
    }
    free(seen);

    if (result == NULL)
    {
        result = malloc(5);
        if (result != NULL)
        {
            snprintf(result, 5, "%s", "None");
        }
    }

    return result;
}

int main(void)
{
    const char *text1 = "This is a test, this is only a test.";
    char *repeated = find_first_repeated_word(text1);
    if (repeated != NULL)
    {
        printf("%s\n", repeated);
        free(repeated);
    }
    else
    {
        printf("None\n");
    }

    const char *text2 = "No repetition here";
    repeated = find_first_repeated_word(text2);
    if (repeated != NULL)
    {
        printf("%s\n", repeated);
        free(repeated);
    }
    else
    {
        printf("None\n");
    }

    return 0;
}