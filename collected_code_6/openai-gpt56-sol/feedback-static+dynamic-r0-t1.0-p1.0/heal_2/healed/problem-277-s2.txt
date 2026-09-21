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

static char *duplicate_string(const char *source, size_t maximum_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || maximum_length == SIZE_MAX) {
        return NULL;
    }

    terminator = memchr(source, '\0', maximum_length + 1U);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void free_dictionary(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t i = 0U; i < dictionary->size; ++i) {
            free(dictionary->entries[i].key);
        }
        free(dictionary->entries);
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
}

static int filter_dictionary_by_value(const Dictionary *source,
                                      int minimum_value,
                                      int maximum_value,
                                      size_t maximum_key_length,
                                      Dictionary *result)
{
    Dictionary filtered = {NULL, 0U};
    size_t match_count = 0U;
    size_t output_index = 0U;

    if (source == NULL ||
        result == NULL ||
        source == result ||
        minimum_value > maximum_value ||
        maximum_key_length == SIZE_MAX ||
        (source->size != 0U && source->entries == NULL)) {
        return -1;
    }

    for (size_t i = 0U; i < source->size; ++i) {
        const DictionaryEntry *entry = &source->entries[i];

        if (entry->key == NULL ||
            memchr(entry->key, '\0', maximum_key_length + 1U) == NULL) {
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
        if (match_count > SIZE_MAX / sizeof(*filtered.entries)) {
            return -1;
        }

        filtered.entries = calloc(match_count, sizeof(*filtered.entries));
        if (filtered.entries == NULL) {
            return -1;
        }
    }

    for (size_t i = 0U; i < source->size; ++i) {
        const DictionaryEntry *entry = &source->entries[i];

        if (entry->value >= minimum_value &&
            entry->value <= maximum_value) {
            char *key_copy = duplicate_string(entry->key, maximum_key_length);

            if (key_copy == NULL) {
                filtered.size = output_index;
                free_dictionary(&filtered);
                return -1;
            }

            filtered.entries[output_index].key = key_copy;
            filtered.entries[output_index].value = entry->value;
            ++output_index;
            filtered.size = output_index;
        }
    }

    free_dictionary(result);
    *result = filtered;

    return 0;
}

int main(void)
{
    DictionaryEntry source_entries[] = {
        {"apple", 12},
        {"banana", 7},
        {"cherry", 18},
        {"date", 4},
        {"elderberry", 15}
    };
    Dictionary source = {
        source_entries,
        sizeof(source_entries) / sizeof(source_entries[0])
    };
    Dictionary filtered = {NULL, 0U};
    const size_t maximum_key_length = 64U;

    if (filter_dictionary_by_value(&source,
                                   10,
                                   15,
                                   maximum_key_length,
                                   &filtered) != 0) {
        fputs("Failed to filter dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < filtered.size; ++i) {
        if (printf("%s: %d\n",
                   filtered.entries[i].key,
                   filtered.entries[i].value) < 0) {
            free_dictionary(&filtered);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(&filtered);
    return EXIT_SUCCESS;
}