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

typedef int (*ValuePredicate)(int value);

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

    if (length > 0U) {
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

static int filter_dictionary(const Dictionary *source,
                             ValuePredicate predicate,
                             size_t maximum_key_length,
                             Dictionary *result)
{
    size_t count = 0U;
    size_t output_index = 0U;
    unsigned char *matches = NULL;
    Dictionary temporary = { NULL, 0U };

    if (source == NULL || predicate == NULL || result == NULL ||
        source == result || maximum_key_length == 0U) {
        return -1;
    }

    if (source->size == 0U) {
        result->entries = NULL;
        result->size = 0U;
        return 0;
    }

    if (source->entries == NULL ||
        source->size > SIZE_MAX / sizeof(*matches)) {
        return -1;
    }

    matches = calloc(source->size, sizeof(*matches));
    if (matches == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < source->size; ++i) {
        const DictionaryEntry *entry = &source->entries[i];

        if (entry->key == NULL ||
            memchr(entry->key, '\0', maximum_key_length) == NULL) {
            free(matches);
            return -1;
        }

        if (predicate(entry->value) != 0) {
            matches[i] = 1U;
            ++count;
        }
    }

    if (count == 0U) {
        free(matches);
        result->entries = NULL;
        result->size = 0U;
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*temporary.entries)) {
        free(matches);
        return -1;
    }

    temporary.entries = calloc(count, sizeof(*temporary.entries));
    if (temporary.entries == NULL) {
        free(matches);
        return -1;
    }

    for (size_t i = 0U; i < source->size; ++i) {
        char *key_copy;

        if (matches[i] == 0U) {
            continue;
        }

        key_copy = duplicate_string(source->entries[i].key,
                                    maximum_key_length);
        if (key_copy == NULL) {
            temporary.size = output_index;
            free_dictionary(&temporary);
            free(matches);
            return -1;
        }

        temporary.entries[output_index].key = key_copy;
        temporary.entries[output_index].value = source->entries[i].value;
        ++output_index;
        temporary.size = output_index;
    }

    free(matches);
    *result = temporary;

    return 0;
}

static int is_positive(int value)
{
    return value > 0;
}

int main(void)
{
    DictionaryEntry source_entries[] = {
        { "apple", 5 },
        { "banana", -2 },
        { "orange", 8 },
        { "pear", 0 }
    };
    Dictionary source = {
        source_entries,
        sizeof(source_entries) / sizeof(source_entries[0])
    };
    Dictionary filtered = { NULL, 0U };
    const size_t maximum_key_length = 256U;

    if (filter_dictionary(&source, is_positive, maximum_key_length,
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