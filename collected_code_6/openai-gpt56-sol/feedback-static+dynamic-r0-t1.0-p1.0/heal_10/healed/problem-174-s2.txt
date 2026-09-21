#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH (1024U * 1024U)

typedef struct {
    const char *key;
    const char *value;
} KeyValuePair;

typedef struct {
    char *key;
    size_t key_length;
    char **values;
    size_t value_count;
    size_t value_capacity;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t entry_count;
    size_t entry_capacity;
} Dictionary;

static int bounded_string_length(const char *string, size_t limit,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL || limit == 0U) {
        return -1;
    }

    terminator = memchr(string, '\0', limit);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
}

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length > MAX_STRING_LENGTH ||
        length == SIZE_MAX) {
        return NULL;
    }

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

static void dictionary_destroy(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t i = 0U; i < dictionary->entry_count; ++i) {
            DictionaryEntry *entry = &dictionary->entries[i];

            free(entry->key);

            if (entry->values != NULL) {
                for (size_t j = 0U; j < entry->value_count; ++j) {
                    free(entry->values[j]);
                }
            }

            free(entry->values);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->entry_count = 0U;
    dictionary->entry_capacity = 0U;
}

static DictionaryEntry *dictionary_find_entry(Dictionary *dictionary,
                                               const char *key,
                                               size_t key_length)
{
    if (dictionary == NULL || key == NULL ||
        key_length > MAX_STRING_LENGTH ||
        dictionary->entry_count > dictionary->entry_capacity ||
        (dictionary->entry_count != 0U && dictionary->entries == NULL)) {
        return NULL;
    }

    for (size_t i = 0U; i < dictionary->entry_count; ++i) {
        DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key != NULL &&
            entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return entry;
        }
    }

    return NULL;
}

static int dictionary_grow_entries(Dictionary *dictionary)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL ||
        dictionary->entry_count > dictionary->entry_capacity) {
        return -1;
    }

    if (dictionary->entry_capacity == 0U) {
        new_capacity = 4U;
    } else {
        if (dictionary->entry_capacity > SIZE_MAX / 2U) {
            return -1;
        }
        new_capacity = dictionary->entry_capacity * 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return -1;
    }

    new_entries = realloc(dictionary->entries,
                          new_capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return -1;
    }

    dictionary->entries = new_entries;
    dictionary->entry_capacity = new_capacity;
    return 0;
}

static int entry_grow_values(DictionaryEntry *entry)
{
    size_t new_capacity;
    char **new_values;

    if (entry == NULL || entry->value_count > entry->value_capacity) {
        return -1;
    }

    if (entry->value_capacity == 0U) {
        new_capacity = 4U;
    } else {
        if (entry->value_capacity > SIZE_MAX / 2U) {
            return -1;
        }
        new_capacity = entry->value_capacity * 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_values)) {
        return -1;
    }

    new_values = realloc(entry->values,
                         new_capacity * sizeof(*new_values));
    if (new_values == NULL) {
        return -1;
    }

    entry->values = new_values;
    entry->value_capacity = new_capacity;
    return 0;
}

static int entry_add_value(DictionaryEntry *entry, const char *value,
                           size_t value_length)
{
    char *value_copy;

    if (entry == NULL || value == NULL ||
        value_length > MAX_STRING_LENGTH ||
        entry->value_count > entry->value_capacity ||
        (entry->value_count != 0U && entry->values == NULL)) {
        return -1;
    }

    if (entry->value_count == entry->value_capacity &&
        entry_grow_values(entry) != 0) {
        return -1;
    }

    value_copy = duplicate_string(value, value_length);
    if (value_copy == NULL) {
        return -1;
    }

    entry->values[entry->value_count] = value_copy;
    ++entry->value_count;
    return 0;
}

static int dictionary_add(Dictionary *dictionary, const char *key,
                          size_t key_length, const char *value,
                          size_t value_length)
{
    DictionaryEntry *entry;
    char *key_copy;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length > MAX_STRING_LENGTH ||
        value_length > MAX_STRING_LENGTH ||
        dictionary->entry_count > dictionary->entry_capacity ||
        (dictionary->entry_count != 0U && dictionary->entries == NULL)) {
        return -1;
    }

    entry = dictionary_find_entry(dictionary, key, key_length);
    if (entry != NULL) {
        return entry_add_value(entry, value, value_length);
    }

    if (dictionary->entry_count == dictionary->entry_capacity &&
        dictionary_grow_entries(dictionary) != 0) {
        return -1;
    }

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    entry = &dictionary->entries[dictionary->entry_count];
    entry->key = key_copy;
    entry->key_length = key_length;
    entry->values = NULL;
    entry->value_count = 0U;
    entry->value_capacity = 0U;

    if (entry_add_value(entry, value, value_length) != 0) {
        free(entry->key);
        entry->key = NULL;
        entry->key_length = 0U;
        return -1;
    }

    ++dictionary->entry_count;
    return 0;
}

static int group_pairs(const KeyValuePair *pairs, size_t pair_count,
                       Dictionary *result)
{
    Dictionary temporary = {NULL, 0U, 0U};

    if (result == NULL || (pairs == NULL && pair_count != 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < pair_count; ++i) {
        size_t key_length;
        size_t value_length;

        if (bounded_string_length(pairs[i].key,
                                  (size_t)MAX_STRING_LENGTH + 1U,
                                  &key_length) != 0 ||
            bounded_string_length(pairs[i].value,
                                  (size_t)MAX_STRING_LENGTH + 1U,
                                  &value_length) != 0 ||
            dictionary_add(&temporary, pairs[i].key, key_length,
                           pairs[i].value, value_length) != 0) {
            dictionary_destroy(&temporary);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = temporary;
    return 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    if (dictionary == NULL ||
        dictionary->entry_count > dictionary->entry_capacity ||
        (dictionary->entry_count != 0U && dictionary->entries == NULL)) {
        return -1;
    }

    for (size_t i = 0U; i < dictionary->entry_count; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key == NULL ||
            entry->value_count > entry->value_capacity ||
            (entry->value_count != 0U && entry->values == NULL) ||
            fputs(entry->key, stdout) == EOF ||
            fputs(": [", stdout) == EOF) {
            return -1;
        }

        for (size_t j = 0U; j < entry->value_count; ++j) {
            if (entry->values[j] == NULL ||
                (j != 0U && fputs(", ", stdout) == EOF) ||
                fputs(entry->values[j], stdout) == EOF) {
                return -1;
            }
        }

        if (fputs("]\n", stdout) == EOF) {
            return -1;
        }
    }

    return ferror(stdout) != 0 ? -1 : 0;
}

int main(void)
{
    static const KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "blue"},
        {"fruit", "orange"}
    };
    Dictionary dictionary = {NULL, 0U, 0U};
    const size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);
    int status = EXIT_SUCCESS;

    if (group_pairs(pairs, pair_count, &dictionary) != 0) {
        fputs("Failed to group key-value pairs.\n", stderr);
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    if (dictionary_print(&dictionary) != 0) {
        fputs("Failed to print dictionary.\n", stderr);
        status = EXIT_FAILURE;
    }

    dictionary_destroy(&dictionary);
    return status;
}