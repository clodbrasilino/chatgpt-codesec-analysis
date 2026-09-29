#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
} Dictionary;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (index = 0U; index < dictionary->size; ++index) {
            free(dictionary->entries[index].key);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
}

static int dictionary_filter_by_value(
    const Dictionary *source,
    int minimum_value,
    int maximum_value,
    Dictionary *result)
{
    Dictionary temporary = {NULL, 0U};
    size_t match_count = 0U;
    size_t index;

    if (source == NULL || result == NULL || source == result ||
        minimum_value > maximum_value) {
        return -1;
    }

    if ((source->size != 0U && source->entries == NULL) ||
        (result->size != 0U && result->entries == NULL)) {
        return -1;
    }

    for (index = 0U; index < source->size; ++index) {
        const DictionaryEntry *entry = &source->entries[index];

        if (entry->key == NULL) {
            return -1;
        }

        if (entry->value >= minimum_value &&
            entry->value <= maximum_value) {
            if (match_count == SIZE_MAX) {
                return -1;
            }
            ++match_count;
        }
    }

    if (match_count != 0U) {
        if (match_count > SIZE_MAX / sizeof(*temporary.entries)) {
            return -1;
        }

        temporary.entries = calloc(match_count, sizeof(*temporary.entries));
        if (temporary.entries == NULL) {
            return -1;
        }

        for (index = 0U; index < source->size; ++index) {
            const DictionaryEntry *source_entry = &source->entries[index];
            DictionaryEntry *destination_entry;

            if (source_entry->value < minimum_value ||
                source_entry->value > maximum_value) {
                continue;
            }

            destination_entry = &temporary.entries[temporary.size];
            destination_entry->key = duplicate_string(source_entry->key);

            if (destination_entry->key == NULL) {
                dictionary_destroy(&temporary);
                return -1;
            }

            destination_entry->value = source_entry->value;
            ++temporary.size;
        }
    }

    dictionary_destroy(result);
    *result = temporary;

    return 0;
}

int main(void)
{
    char apple[] = "apple";
    char banana[] = "banana";
    char cherry[] = "cherry";
    char date[] = "date";
    char elderberry[] = "elderberry";

    DictionaryEntry entries[] = {
        {apple, 10},
        {banana, 25},
        {cherry, 40},
        {date, 15},
        {elderberry, 50}
    };

    Dictionary source = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };

    Dictionary filtered = {NULL, 0U};
    size_t index;

    if (dictionary_filter_by_value(&source, 15, 40, &filtered) != 0) {
        fputs("Failed to filter dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < filtered.size; ++index) {
        if (printf("%s: %d\n",
                   filtered.entries[index].key,
                   filtered.entries[index].value) < 0) {
            dictionary_destroy(&filtered);
            return EXIT_FAILURE;
        }
    }

    dictionary_destroy(&filtered);
    return EXIT_SUCCESS;
}