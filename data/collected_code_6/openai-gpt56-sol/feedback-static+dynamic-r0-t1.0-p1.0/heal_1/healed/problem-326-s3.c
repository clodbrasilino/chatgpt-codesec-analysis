#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *word;
    size_t count;
} WordEntry;

static int find_most_frequent_word(const char *const strings[],
                                   size_t string_count,
                                   const char **result,
                                   size_t *occurrences)
{
    WordEntry *entries;
    size_t entry_count = 0U;
    size_t best_index = 0U;
    size_t i;

    if (strings == NULL || result == NULL || occurrences == NULL ||
        string_count == 0U ||
        string_count > SIZE_MAX / sizeof(*entries)) {
        return -1;
    }

    *result = NULL;
    *occurrences = 0U;

    entries = calloc(string_count, sizeof(*entries));
    if (entries == NULL) {
        return -1;
    }

    for (i = 0U; i < string_count; ++i) {
        size_t j;

        if (strings[i] == NULL) {
            continue;
        }

        for (j = 0U; j < entry_count; ++j) {
            if (strcmp(entries[j].word, strings[i]) == 0) {
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

    *result = entries[best_index].word;
    *occurrences = entries[best_index].count;

    free(entries);
    return 0;
}

int main(void)
{
    const char *strings[] = {
        "apple", "banana", "apple", "orange",
        "banana", "apple", "pear", "banana"
    };
    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    const char *word = NULL;
    size_t occurrences = 0U;

    if (find_most_frequent_word(strings, string_count,
                                &word, &occurrences) != 0) {
        fputs("Unable to determine the most frequent word.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s %zu\n", word, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}