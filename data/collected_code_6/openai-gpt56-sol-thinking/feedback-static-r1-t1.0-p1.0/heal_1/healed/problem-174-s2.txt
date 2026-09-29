#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    size_t key_length;
    const char *value;
    size_t value_length;
} KeyValuePair;

typedef struct {
    char *data;
    size_t length;
} DictionaryValue;

typedef struct {
    char *key;
    size_t key_length;
    DictionaryValue *values;
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
    if (dictionary == NULL) {
        return;
    }

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
            free(dictionary->entries[i].values[j].data);
        }

        free(dictionary->entries[i].values);
    }

    free(dictionary->entries);
    dictionary_init(dictionary);
}

static GroupStatus duplicate_bytes(const char *source,
                                   size_t length,
                                   char **destination)
{
    char *copy;
    size_t i;

    if (source == NULL || destination == NULL) {
        return GROUP_INVALID_ARGUMENT;
    }

    *destination = NULL;

    if (length == SIZE_MAX) {
        return GROUP_OUT_OF_MEMORY;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return GROUP_OUT_OF_MEMORY;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    *destination = copy;

    return GROUP_SUCCESS;
}

static GroupStatus reserve_entries(Dictionary *dictionary, size_t required)
{
    size_t new_capacity;
    const size_t maximum_capacity = SIZE_MAX / sizeof(*dictionary->entries);
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return GROUP_INVALID_ARGUMENT;
    }

    if (required <= dictionary->entry_capacity) {
        return GROUP_SUCCESS;
    }

    if (required > maximum_capacity) {
        return GROUP_OUT_OF_MEMORY;
    }

    new_capacity = dictionary->entry_capacity == 0
                       ? 4
                       : dictionary->entry_capacity;

    if (new_capacity > maximum_capacity) {
        return GROUP_OUT_OF_MEMORY;
    }

    while (new_capacity < required) {
        if (new_capacity > maximum_capacity / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    new_entries = realloc(dictionary->entries,
                          new_capacity * sizeof(*dictionary->entries));
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
    const size_t maximum_capacity = SIZE_MAX / sizeof(*entry->values);
    DictionaryValue *new_values;

    if (entry == NULL) {
        return GROUP_INVALID_ARGUMENT;
    }

    if (required <= entry->value_capacity) {
        return GROUP_SUCCESS;
    }

    if (required > maximum_capacity) {
        return GROUP_OUT_OF_MEMORY;
    }

    new_capacity = entry->value_capacity == 0 ? 4 : entry->value_capacity;

    if (new_capacity > maximum_capacity) {
        return GROUP_OUT_OF_MEMORY;
    }

    while (new_capacity < required) {
        if (new_capacity > maximum_capacity / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    new_values = realloc(entry->values,
                         new_capacity * sizeof(*entry->values));
    if (new_values == NULL) {
        return GROUP_OUT_OF_MEMORY;
    }

    entry->values = new_values;
    entry->value_capacity = new_capacity;

    return GROUP_SUCCESS;
}

static int bytes_equal(const char *left, const char *right, size_t length)
{
    size_t i;

    for (i = 0; i < length; ++i) {
        if (left[i] != right[i]) {
            return 0;
        }
    }

    return 1;
}

static DictionaryEntry *find_entry(Dictionary *dictionary,
                                   const char *key,
                                   size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return NULL;
    }

    for (i = 0; i < dictionary->entry_count; ++i) {
        DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key_length == key_length &&
            bytes_equal(entry->key, key, key_length)) {
            return entry;
        }
    }

    return NULL;
}

static GroupStatus add_pair(Dictionary *dictionary, const KeyValuePair *pair)
{
    DictionaryEntry *entry;
    GroupStatus status;
    char *value_copy;

    if (dictionary == NULL || pair == NULL ||
        pair->key == NULL || pair->value == NULL) {
        return GROUP_INVALID_ARGUMENT;
    }

    if (pair->key_length == SIZE_MAX || pair->value_length == SIZE_MAX) {
        return GROUP_OUT_OF_MEMORY;
    }

    entry = find_entry(dictionary, pair->key, pair->key_length);

    if (entry != NULL) {
        if (entry->value_count == SIZE_MAX) {
            return GROUP_OUT_OF_MEMORY;
        }

        status = duplicate_bytes(pair->value,
                                 pair->value_length,
                                 &value_copy);
        if (status != GROUP_SUCCESS) {
            return status;
        }

        status = reserve_values(entry, entry->value_count + 1);
        if (status != GROUP_SUCCESS) {
            free(value_copy);
            return status;
        }

        entry->values[entry->value_count].data = value_copy;
        entry->values[entry->value_count].length = pair->value_length;
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

    {
        DictionaryEntry new_entry;

        new_entry.key = NULL;
        new_entry.key_length = 0;
        new_entry.values = NULL;
        new_entry.value_count = 0;
        new_entry.value_capacity = 0;

        status = duplicate_bytes(pair->key,
                                 pair->key_length,
                                 &new_entry.key);
        if (status != GROUP_SUCCESS) {
            return status;
        }

        new_entry.key_length = pair->key_length;

        status = reserve_values(&new_entry, 1);
        if (status != GROUP_SUCCESS) {
            free(new_entry.key);
            return status;
        }

        status = duplicate_bytes(pair->value,
                                 pair->value_length,
                                 &value_copy);
        if (status != GROUP_SUCCESS) {
            free(new_entry.values);
            free(new_entry.key);
            return status;
        }

        new_entry.values[0].data = value_copy;
        new_entry.values[0].length = pair->value_length;
        new_entry.value_count = 1;

        dictionary->entries[dictionary->entry_count] = new_entry;
        ++dictionary->entry_count;
    }

    return GROUP_SUCCESS;
}

GroupStatus group_pairs(const KeyValuePair *pairs,
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
        GroupStatus status = add_pair(result, &pairs[i]);

        if (status != GROUP_SUCCESS) {
            dictionary_destroy(result);
            return status;
        }
    }

    return GROUP_SUCCESS;
}

static int print_bytes(const char *data, size_t length)
{
    if (data == NULL) {
        return -1;
    }

    if (length != 0 && fwrite(data, 1, length, stdout) != length) {
        return -1;
    }

    return 0;
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
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (fputs("  ", stdout) == EOF) {
            return -1;
        }

        if (print_bytes(entry->key, entry->key_length) != 0) {
            return -1;
        }

        if (fputs(": [", stdout) == EOF) {
            return -1;
        }

        for (j = 0; j < entry->value_count; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (print_bytes(entry->values[j].data,
                            entry->values[j].length) != 0) {
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
        {"fruit", sizeof("fruit") - 1, "apple", sizeof("apple") - 1},
        {"color", sizeof("color") - 1, "red", sizeof("red") - 1},
        {"fruit", sizeof("fruit") - 1, "banana", sizeof("banana") - 1},
        {"color", sizeof("color") - 1, "blue", sizeof("blue") - 1},
        {"fruit", sizeof("fruit") - 1, "orange", sizeof("orange") - 1},
        {"shape", sizeof("shape") - 1, "circle", sizeof("circle") - 1}
    };
    Dictionary dictionary;
    GroupStatus status;
    int print_status;

    status = group_pairs(pairs,
                         sizeof(pairs) / sizeof(pairs[0]),
                         &dictionary);
    if (status != GROUP_SUCCESS) {
        if (fputs("Failed to group key-value pairs\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    print_status = print_dictionary(&dictionary);
    dictionary_destroy(&dictionary);

    if (print_status != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}