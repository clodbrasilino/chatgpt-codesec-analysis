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

typedef enum {
    GROUP_SUCCESS = 0,
    GROUP_INVALID_ARGUMENT,
    GROUP_OUT_OF_MEMORY
} GroupStatus;

static void dictionary_init(Dictionary *dictionary)
{
    dictionary->entries = NULL;
    dictionary->entry_count = 0;
    dictionary->entry_capacity = 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;
    size_t j;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->entry_count; ++i) {
        free(dictionary->entries[i].key);

        for (j = 0; j < dictionary->entries[i].value_count; ++j) {
            free(dictionary->entries[i].values[j]);
        }

        free(dictionary->entries[i].values);
    }

    free(dictionary->entries);
    dictionary_init(dictionary);
}

static GroupStatus duplicate_string(const char *source, char **destination)
{
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL) {
        return GROUP_INVALID_ARGUMENT;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        return GROUP_OUT_OF_MEMORY;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return GROUP_OUT_OF_MEMORY;
    }

    memcpy(copy, source, length + 1);
    *destination = copy;

    return GROUP_SUCCESS;
}

static GroupStatus reserve_entries(Dictionary *dictionary, size_t required)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary->entry_capacity >= required) {
        return GROUP_SUCCESS;
    }

    new_capacity = dictionary->entry_capacity == 0
                       ? 4
                       : dictionary->entry_capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return GROUP_OUT_OF_MEMORY;
    }

    new_entries = realloc(dictionary->entries,
                          new_capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return GROUP_OUT_OF_MEMORY;
    }

    dictionary->entries = new_entries;
    dictionary->entry_capacity = new_capacity;

    return GROUP_SUCCESS;
}

static GroupStatus reserve_values(DictionaryEntry *entry, size_t required)
{
    size_t new_capacity;
    char **new_values;

    if (entry->value_capacity >= required) {
        return GROUP_SUCCESS;
    }

    new_capacity = entry->value_capacity == 0 ? 4 : entry->value_capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_values)) {
        return GROUP_OUT_OF_MEMORY;
    }

    new_values = realloc(entry->values,
                         new_capacity * sizeof(*new_values));
    if (new_values == NULL) {
        return GROUP_OUT_OF_MEMORY;
    }

    entry->values = new_values;
    entry->value_capacity = new_capacity;

    return GROUP_SUCCESS;
}

static DictionaryEntry *find_entry(Dictionary *dictionary, const char *key)
{
    size_t i;

    for (i = 0; i < dictionary->entry_count; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
            return &dictionary->entries[i];
        }
    }

    return NULL;
}

static GroupStatus add_pair(Dictionary *dictionary,
                            const char *key,
                            const char *value)
{
    DictionaryEntry *entry;
    GroupStatus status;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return GROUP_INVALID_ARGUMENT;
    }

    entry = find_entry(dictionary, key);

    if (entry != NULL) {
        if (entry->value_count == SIZE_MAX) {
            return GROUP_OUT_OF_MEMORY;
        }

        status = duplicate_string(value, &value_copy);
        if (status != GROUP_SUCCESS) {
            return status;
        }

        status = reserve_values(entry, entry->value_count + 1);
        if (status != GROUP_SUCCESS) {
            free(value_copy);
            return status;
        }

        entry->values[entry->value_count] = value_copy;
        ++entry->value_count;

        return GROUP_SUCCESS;
    }

    if (dictionary->entry_count == SIZE_MAX) {
        return GROUP_OUT_OF_MEMORY;
    }

    status = reserve_entries(dictionary, dictionary->entry_count + 1);
    if (status != GROUP_SUCCESS) {
        return status;
    }

    status = duplicate_string(key, &key_copy);
    if (status != GROUP_SUCCESS) {
        return status;
    }

    status = duplicate_string(value, &value_copy);
    if (status != GROUP_SUCCESS) {
        free(key_copy);
        return status;
    }

    entry = &dictionary->entries[dictionary->entry_count];
    entry->key = key_copy;
    entry->values = NULL;
    entry->value_count = 0;
    entry->value_capacity = 0;

    status = reserve_values(entry, 1);
    if (status != GROUP_SUCCESS) {
        free(value_copy);
        free(key_copy);
        entry->key = NULL;
        return status;
    }

    entry->values[entry->value_count] = value_copy;
    ++entry->value_count;
    ++dictionary->entry_count;

    return GROUP_SUCCESS;
}

static GroupStatus group_pairs(const KeyValuePair *pairs,
                               size_t pair_count,
                               Dictionary *result)
{
    size_t i;

    if (result == NULL) {
        return GROUP_INVALID_ARGUMENT;
    }

    dictionary_init(result);

    if (pairs == NULL && pair_count != 0) {
        return GROUP_INVALID_ARGUMENT;
    }

    for (i = 0; i < pair_count; ++i) {
        GroupStatus status = add_pair(result, pairs[i].key, pairs[i].value);

        if (status != GROUP_SUCCESS) {
            dictionary_destroy(result);
            return status;
        }
    }

    return GROUP_SUCCESS;
}

static int print_dictionary(const Dictionary *dictionary)
{
    size_t i;
    size_t j;

    if (dictionary == NULL) {
        return -1;
    }

    if (fputs("{\n", stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < dictionary->entry_count; ++i) {
        if (printf("  %s: [", dictionary->entries[i].key) < 0) {
            return -1;
        }

        for (j = 0; j < dictionary->entries[i].value_count; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%s", dictionary->entries[i].values[j]) < 0) {
                return -1;
            }
        }

        if (fputs("]\n", stdout) == EOF) {
            return -1;
        }
    }

    if (fputs("}\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "blue"},
        {"fruit", "orange"},
        {"shape", "circle"}
    };
    Dictionary dictionary;
    GroupStatus status;
    int print_status;

    status = group_pairs(pairs,
                         sizeof(pairs) / sizeof(pairs[0]),
                         &dictionary);
    if (status != GROUP_SUCCESS) {
        fputs("Failed to group key-value pairs\n", stderr);
        return EXIT_FAILURE;
    }

    print_status = print_dictionary(&dictionary);
    dictionary_destroy(&dictionary);

    if (print_status != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}