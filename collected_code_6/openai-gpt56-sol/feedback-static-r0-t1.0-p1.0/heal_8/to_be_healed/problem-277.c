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

    if (source == NULL || maximum_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', maximum_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t index = 0U; index < dictionary->size; ++index) {
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
    size_t maximum_key_length,
    Dictionary *result)
{
    size_t count = 0U;
    size_t output_index = 0U;
    DictionaryEntry *new_entries = NULL;

    if (source == NULL ||
        result == NULL ||
        source == result ||
        minimum_value > maximum_value ||
        maximum_key_length == 0U) {
        return -1;
    }

    if ((source->size != 0U && source->entries == NULL) ||
        result->entries != NULL ||
        result->size != 0U) {
        return -1;
    }

    for (size_t index = 0U; index < source->size; ++index) {
        const DictionaryEntry *entry = &source->entries[index];

        if (entry->key == NULL ||
            memchr(entry->key, '\0', maximum_key_length) == NULL) {
            return -1;
        }

        if (entry->value >= minimum_value &&
            entry->value <= maximum_value) {
            if (count == SIZE_MAX) {
                return -1;
            }
            ++count;
        }
    }

    if (count == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*new_entries)) {
        return -1;
    }

    new_entries = calloc(count, sizeof(*new_entries));
    if (new_entries == NULL) {
        return -1;
    }

    for (size_t index = 0U; index < source->size; ++index) {
        const DictionaryEntry *source_entry = &source->entries[index];

        if (source_entry->value < minimum_value ||
            source_entry->value > maximum_value) {
            continue;
        }

        if (output_index >= count) {
            for (size_t cleanup_index = 0U;
                 cleanup_index < output_index;
                 ++cleanup_index) {
                free(new_entries[cleanup_index].key);
            }
            free(new_entries);
            return -1;
        }

        new_entries[output_index].key =
            duplicate_string(source_entry->key, maximum_key_length);

        if (new_entries[output_index].key == NULL) {
            for (size_t cleanup_index = 0U;
                 cleanup_index < output_index;
                 ++cleanup_index) {
                free(new_entries[cleanup_index].key);
            }
            free(new_entries);
            return -1;
        }

        new_entries[output_index].value = source_entry->value;
        ++output_index;
    }

    result->entries = new_entries;
    result->size = output_index;
    return 0;
}

int main(void)
{
    enum { MAXIMUM_KEY_LENGTH = 256 };

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

    if (dictionary_filter_by_value(
            &source,
            15,
            40,
            MAXIMUM_KEY_LENGTH,
            &filtered) != 0) {
        fputs("Failed to filter dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < filtered.size; ++index) {
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