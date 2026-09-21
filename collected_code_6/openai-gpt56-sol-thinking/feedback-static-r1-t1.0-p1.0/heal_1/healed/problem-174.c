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

static char *copy_text(const char *source, size_t length)
{
    char *copy;
    size_t index;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (index = 0; index < length; ++index) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    return copy;
}

static int text_equals(const char *left, size_t left_length,
                       const char *right, size_t right_length)
{
    size_t index;

    if (left_length != right_length) {
        return 0;
    }

    for (index = 0; index < left_length; ++index) {
        if (left[index] != right[index]) {
            return 0;
        }
    }

    return 1;
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

    if (dictionary->entry_capacity == 0) {
        capacity = maximum < 4 ? maximum : 4;
    } else {
        capacity = dictionary->entry_capacity;
    }

    while (capacity < required) {
        if (capacity > maximum / 2) {
            capacity = maximum;
        } else {
            capacity *= 2;
        }
    }

    entries = realloc(dictionary->entries,
                      capacity * sizeof(*dictionary->entries));
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
    DictionaryValue *values;

    if (required <= entry->value_capacity) {
        return 1;
    }

    maximum = SIZE_MAX / sizeof(*entry->values);
    if (required > maximum) {
        return 0;
    }

    if (entry->value_capacity == 0) {
        capacity = maximum < 4 ? maximum : 4;
    } else {
        capacity = entry->value_capacity;
    }

    while (capacity < required) {
        if (capacity > maximum / 2) {
            capacity = maximum;
        } else {
            capacity *= 2;
        }
    }

    values = realloc(entry->values, capacity * sizeof(*entry->values));
    if (values == NULL) {
        return 0;
    }

    entry->values = values;
    entry->value_capacity = capacity;
    return 1;
}

static DictionaryEntry *find_entry(Dictionary *dictionary,
                                   const char *key,
                                   size_t key_length)
{
    size_t index;

    for (index = 0; index < dictionary->entry_count; ++index) {
        DictionaryEntry *entry = &dictionary->entries[index];

        if (text_equals(entry->key, entry->key_length, key, key_length)) {
            return entry;
        }
    }

    return NULL;
}

static int add_pair(Dictionary *dictionary,
                    const char *key,
                    size_t key_length,
                    const char *value,
                    size_t value_length)
{
    DictionaryEntry *entry;
    DictionaryEntry new_entry;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return 0;
    }

    entry = find_entry(dictionary, key, key_length);
    if (entry != NULL) {
        if (entry->value_count == SIZE_MAX) {
            return 0;
        }

        value_copy = copy_text(value, value_length);
        if (value_copy == NULL) {
            return 0;
        }

        if (!reserve_values(entry, entry->value_count + 1)) {
            free(value_copy);
            return 0;
        }

        entry->values[entry->value_count].data = value_copy;
        entry->values[entry->value_count].length = value_length;
        ++entry->value_count;
        return 1;
    }

    if (dictionary->entry_count == SIZE_MAX) {
        return 0;
    }

    key_copy = copy_text(key, key_length);
    if (key_copy == NULL) {
        return 0;
    }

    value_copy = copy_text(value, value_length);
    if (value_copy == NULL) {
        free(key_copy);
        return 0;
    }

    new_entry.key = key_copy;
    new_entry.key_length = key_length;
    new_entry.values = NULL;
    new_entry.value_count = 0;
    new_entry.value_capacity = 0;

    if (!reserve_values(&new_entry, 1)) {
        free(value_copy);
        free(key_copy);
        return 0;
    }

    new_entry.values[0].data = value_copy;
    new_entry.values[0].length = value_length;
    new_entry.value_count = 1;

    if (!reserve_entries(dictionary, dictionary->entry_count + 1)) {
        free(new_entry.values);
        free(value_copy);
        free(key_copy);
        return 0;
    }

    dictionary->entries[dictionary->entry_count] = new_entry;
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

    for (entry_index = 0; entry_index < dictionary->entry_count;
         ++entry_index) {
        DictionaryEntry *entry = &dictionary->entries[entry_index];

        for (value_index = 0; value_index < entry->value_count;
             ++value_index) {
            free(entry->values[value_index].data);
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
        if (!add_pair(dictionary,
                      pairs[index].key,
                      pairs[index].key_length,
                      pairs[index].value,
                      pairs[index].value_length)) {
            destroy_dictionary(dictionary);
            return NULL;
        }
    }

    return dictionary;
}

static int write_text(const char *text, size_t length)
{
    if (length == 0) {
        return 1;
    }

    return fwrite(text, 1, length, stdout) == length;
}

static int print_dictionary(const Dictionary *dictionary)
{
    size_t entry_index;
    size_t value_index;

    if (dictionary == NULL) {
        return 0;
    }

    for (entry_index = 0; entry_index < dictionary->entry_count;
         ++entry_index) {
        const DictionaryEntry *entry = &dictionary->entries[entry_index];

        if (!write_text(entry->key, entry->key_length)) {
            return 0;
        }

        if (fputs(": [", stdout) == EOF) {
            return 0;
        }

        for (value_index = 0; value_index < entry->value_count;
             ++value_index) {
            if (value_index != 0 && fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (!write_text(entry->values[value_index].data,
                            entry->values[value_index].length)) {
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
        {"fruit", sizeof("fruit") - 1, "apple", sizeof("apple") - 1},
        {"color", sizeof("color") - 1, "blue", sizeof("blue") - 1},
        {"fruit", sizeof("fruit") - 1, "banana", sizeof("banana") - 1},
        {"animal", sizeof("animal") - 1, "cat", sizeof("cat") - 1},
        {"color", sizeof("color") - 1, "green", sizeof("green") - 1},
        {"fruit", sizeof("fruit") - 1, "orange", sizeof("orange") - 1}
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