#include <stdio.h>
#include <string.h>
#include <stddef.h>

const char *get_most_frequent_word(const char *const words[], size_t count, size_t *out_count)
{
    size_t i;
    size_t j;
    size_t max_count;
    size_t current_count;
    const char *most_frequent;

    if (out_count == NULL)
    {
        return NULL;
    }

    *out_count = 0;

    if (words == NULL || count == 0)
    {
        return NULL;
    }

    max_count = 0;
    most_frequent = NULL;

    for (i = 0; i < count; i++)
    {
        if (words[i] == NULL)
        {
            continue;
        }

        current_count = 0;

        for (j = 0; j < count; j++)
        {
            if (words[j] != NULL && strcmp(words[i], words[j]) == 0)
            {
                current_count++;
            }
        }

        if (current_count > max_count)
        {
            max_count = current_count;
            most_frequent = words[i];
        }
    }

    *out_count = max_count;

    return most_frequent;
}

int main(void)
{
    const char *words[] = {
        "apple",
        "banana",
        "apple",
        "cherry",
        "banana",
        "apple",
        "date",
        "banana"
    };
    size_t count;
    size_t occurrences;
    const char *result;

    count = sizeof(words) / sizeof(words[0]);
    occurrences = 0;

    result = get_most_frequent_word(words, count, &occurrences);

    if (result != NULL && occurrences > 0)
    {
        printf("Most frequent word: \"%s\" (%zu occurrence%s)\n",
               result, occurrences, occurrences == 1 ? "" : "s");
    }
    else
    {
        fprintf(stderr, "Error: no valid word found in the list.\n");
        return 1;
    }

    return 0;
}