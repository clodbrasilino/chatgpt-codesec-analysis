#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *word;
    size_t length;
    size_t count;
} WordEntry;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memmove(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static int find_most_frequent_word(const char *const strings[],
                                   const size_t lengths[],
                                   size_t string_count,
                                   char **result,
                                   size_t *occurrences)
{
    WordEntry *entries;
    size_t entry_count = 0U;
    size_t best_index = 0U;
    size_t i;

    if (result == NULL || occurrences == NULL) {
        return -1;
    }

    *result = NULL;
    *occurrences = 0U;

    if (strings == NULL || lengths == NULL || string_count == 0U ||
        string_count > SIZE_MAX / sizeof(*entries)) {
        return -1;
    }

    entries = calloc(string_count, sizeof(*entries));
    if (entries == NULL) {
        return -1;
    }

    for (i = 0U; i < string_count; ++i) {
        size_t j;

        if (strings[i] == NULL || lengths[i] == SIZE_MAX) {
            continue;
        }

        for (j = 0U; j < entry_count; ++j) {
            if (entries[j].length == lengths[i] &&
                memcmp(entries[j].word, strings[i], lengths[i]) == 0) {
                if (entries[j].count == SIZE_MAX) {
                    free(entries);
                    return -1;
                }

                ++entries[j].count;
                break;
            }
        }

        if (j == entry_count) {
            entries[entry_count].word = strings[i];
            entries[entry_count].length = lengths[i];
            entries[entry_count].count = 1U;
            ++entry_count;
        }
    }

    if (entry_count == 0U) {
        free(entries);
        return -1;
    }

    for (i = 1U; i < entry_count; ++i) {
        if (entries[i].count > entries[best_index].count) {
            best_index = i;
        }
    }

    *result = duplicate_string(entries[best_index].word,
                               entries[best_index].length);
    if (*result != NULL) {
        *occurrences = entries[best_index].count;
    }

    free(entries);
    return *result == NULL ? -1 : 0;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char orange[] = "orange";
    static const char pear[] = "pear";

    const char *strings[] = {
        apple, banana, apple, orange,
        banana, apple, pear, banana
    };
    const size_t lengths[] = {
        sizeof(apple) - 1U,
        sizeof(banana) - 1U,
        sizeof(apple) - 1U,
        sizeof(orange) - 1U,
        sizeof(banana) - 1U,
        sizeof(apple) - 1U,
        sizeof(pear) - 1U,
        sizeof(banana) - 1U
    };
    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    char *word = NULL;
    size_t occurrences = 0U;

    if (find_most_frequent_word(strings, lengths, string_count,
                                &word, &occurrences) != 0) {
        fputs("Unable to determine the most frequent word.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s %zu\n", word, occurrences) < 0) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}