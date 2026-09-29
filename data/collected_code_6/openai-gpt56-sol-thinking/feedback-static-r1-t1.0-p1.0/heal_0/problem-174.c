#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} KeyValuePair;

typedef struct {
    char *key;
    char **values;
    size_t value_count;
    size_t value_capacity;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t entry_count;
    size_t entry_capacity;
} Dictionary;

static char *copy_string(const char *source)
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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static int reserve_entries(Dictionary *dictionary, size_t required)
{
    size_t capacity;
    size_t maximum;
    DictionaryEntry *entries;

    if (required <= dictionary->entry_capacity) {
        return 1;
    }

    maximum = SIZE_MAX / sizeof(*dictionary->entries);
    if (required > maximum) {
        return 0;
    }

    capacity = dictionary->entry_capacity == 0 ? 4 : dictionary->entry_capacity;

    while (capacity < required) {
        if (capacity > maximum / 2) {
            capacity = maximum;
        } else {
            capacity *= 2;
        }
    }

    entries = realloc(dictionary->entries, capacity * sizeof(*entries));
    if (entries == NULL) {
        return 0;
    }

    dictionary->entries = entries;
    dictionary->entry_capacity = capacity;
    return 1;
}

static int reserve_values(DictionaryEntry *entry, size_t required)
{
    size_t capacity;
    size_t maximum;
    char **values;

    if (required <= entry->value_capacity) {
        return 1;
    }

    maximum = SIZE_MAX / sizeof(*entry->values);
    if (required > maximum) {
        return 0;
    }

    capacity = entry->value_capacity == 0 ? 4 : entry->value_capacity;

    while (capacity < required) {
        if (capacity > maximum / 2) {
            capacity = maximum;
        } else {
            capacity *= 2;
        }
    }

    values = realloc(entry->values, capacity * sizeof(*values));
    if (values == NULL) {
        return 0;
    }

    entry->values = values;
    entry->value_capacity = capacity;
    return 1;
}

static DictionaryEntry *find_entry(Dictionary *dictionary, const char *key)
{
    size_t index;

    for (index = 0; index < dictionary->entry_count; ++index) {
        if (strcmp(dictionary->entries[index].key, key) == 0) {
            return &dictionary->entries[index];
        }
    }

    return NULL;
}

static int add_pair(Dictionary *dictionary, const char *key, const char *value)
{
    DictionaryEntry *entry;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return 0;
    }

    entry = find_entry(dictionary, key);
    if (entry != NULL) {
        if (entry->value_count == SIZE_MAX) {
            return 0;
        }

        value_copy = copy_string(value);
        if (value_copy == NULL) {
            return 0;
        }

        if (!reserve_values(entry, entry->value_count + 1)) {
            free(value_copy);
            return 0;
        }

        entry->values[entry->value_count] = value_copy;
        ++entry->value_count;
        return 1;
    }

    if (dictionary->entry_count == SIZE_MAX) {
        return 0;
    }

    key_copy = copy_string(key);
    if (key_copy == NULL) {
        return 0;
    }

    value_copy = copy_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return 0;
    }

    if (!reserve_entries(dictionary, dictionary->entry_count + 1)) {
        free(value_copy);
        free(key_copy);
        return 0;
    }

    entry = &dictionary->entries[dictionary->entry_count];
    entry->key = key_copy;
    entry->values = NULL;
    entry->value_count = 0;
    entry->value_capacity = 0;

    if (!reserve_values(entry, 1)) {
        free(entry->key);
        entry->key = NULL;
        free(value_copy);
        return 0;
    }

    entry->values[0] = value_copy;
    entry->value_count = 1;
    ++dictionary->entry_count;
    return 1;
}

static void destroy_dictionary(Dictionary *dictionary)
{
    size_t entry_index;
    size_t value_index;

    if (dictionary == NULL) {
        return;
    }

    for (entry_index = 0; entry_index < dictionary->entry_count; ++entry_index) {
        DictionaryEntry *entry = &dictionary->entries[entry_index];

        for (value_index = 0; value_index < entry->value_count; ++value_index) {
            free(entry->values[value_index]);
        }

        free(entry->values);
        free(entry->key);
    }

    free(dictionary->entries);
    free(dictionary);
}

static Dictionary *group_pairs(const KeyValuePair *pairs, size_t pair_count)
{
    Dictionary *dictionary;
    size_t index;

    if (pairs == NULL && pair_count != 0) {
        return NULL;
    }

    dictionary = calloc(1, sizeof(*dictionary));
    if (dictionary == NULL) {
        return NULL;
    }

    for (index = 0; index < pair_count; ++index) {
        if (!add_pair(dictionary, pairs[index].key, pairs[index].value)) {
            destroy_dictionary(dictionary);
            return NULL;
        }
    }

    return dictionary;
}

static int print_dictionary(const Dictionary *dictionary)
{
    size_t entry_index;
    size_t value_index;

    if (dictionary == NULL) {
        return 0;
    }

    for (entry_index = 0; entry_index < dictionary->entry_count; ++entry_index) {
        const DictionaryEntry *entry = &dictionary->entries[entry_index];

        if (printf("%s: [", entry->key) < 0) {
            return 0;
        }

        for (value_index = 0; value_index < entry->value_count; ++value_index) {
            if (value_index != 0 && fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (printf("%s", entry->values[value_index]) < 0) {
                return 0;
            }
        }

        if (fputs("]\n", stdout) == EOF) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    const KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "blue"},
        {"fruit", "banana"},
        {"animal", "cat"},
        {"color", "green"},
        {"fruit", "orange"}
    };
    Dictionary *dictionary;
    int status;

    dictionary = group_pairs(pairs, sizeof(pairs) / sizeof(pairs[0]));
    if (dictionary == NULL) {
        fputs("Failed to group key-value pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    status = print_dictionary(dictionary) ? EXIT_SUCCESS : EXIT_FAILURE;
    destroy_dictionary(dictionary);

    if (status != EXIT_SUCCESS) {
        fputs("Failed to write dictionary output.\n", stderr);
    }

    return status;
}