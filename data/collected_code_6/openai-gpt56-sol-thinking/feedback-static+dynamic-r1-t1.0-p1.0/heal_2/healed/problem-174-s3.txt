#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

static char *duplicate_bytes(const char *source, size_t length)
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

    for (index = 0; index < length; index++) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    return copy;
}

static void *grow_array(void *array,
                        size_t current_capacity,
                        size_t minimum_capacity,
                        size_t element_size,
                        size_t *new_capacity_out)
{
    size_t maximum_capacity;
    size_t new_capacity;
    void *resized_array;

    if (element_size == 0 || new_capacity_out == NULL) {
        return NULL;
    }

    if (minimum_capacity <= current_capacity) {
        *new_capacity_out = current_capacity;
        return array;
    }

    maximum_capacity = SIZE_MAX / element_size;
    if (minimum_capacity > maximum_capacity) {
        return NULL;
    }

    new_capacity = current_capacity;

    if (new_capacity == 0) {
        new_capacity = maximum_capacity < 4 ? maximum_capacity : 4;
    }

    while (new_capacity < minimum_capacity) {
        if (new_capacity > maximum_capacity / 2) {
            new_capacity = maximum_capacity;
        } else {
            new_capacity *= 2;
        }
    }

    resized_array = realloc(array, new_capacity * element_size);
    if (resized_array == NULL) {
        return NULL;
    }

    *new_capacity_out = new_capacity;
    return resized_array;
}

static int byte_strings_equal(const char *left,
                              size_t left_length,
                              const char *right,
                              size_t right_length)
{
    size_t index;

    if (left_length != right_length) {
        return 0;
    }

    for (index = 0; index < left_length; index++) {
        if (left[index] != right[index]) {
            return 0;
        }
    }

    return 1;
}

static void free_dictionary_entry(DictionaryEntry *entry)
{
    size_t value_index;

    if (entry == NULL) {
        return;
    }

    free(entry->key);

    for (value_index = 0;
         value_index < entry->value_count;
         value_index++) {
        free(entry->values[value_index].data);
    }

    free(entry->values);

    entry->key = NULL;
    entry->key_length = 0;
    entry->values = NULL;
    entry->value_count = 0;
    entry->value_capacity = 0;
}

static int append_value(DictionaryEntry *entry,
                        const char *value,
                        size_t value_length)
{
    char *value_copy;

    if (entry == NULL || value == NULL ||
        entry->value_count == SIZE_MAX) {
        return 0;
    }

    value_copy = duplicate_bytes(value, value_length);
    if (value_copy == NULL) {
        return 0;
    }

    if (entry->value_count == entry->value_capacity) {
        DictionaryValue *resized_values;
        size_t new_capacity;

        resized_values = grow_array(entry->values,
                                    entry->value_capacity,
                                    entry->value_count + 1,
                                    sizeof(*entry->values),
                                    &new_capacity);

        if (resized_values == NULL) {
            free(value_copy);
            return 0;
        }

        entry->values = resized_values;
        entry->value_capacity = new_capacity;
    }

    entry->values[entry->value_count].data = value_copy;
    entry->values[entry->value_count].length = value_length;
    entry->value_count++;

    return 1;
}

void free_dictionary(Dictionary *dictionary)
{
    size_t entry_index;

    if (dictionary == NULL) {
        return;
    }

    for (entry_index = 0;
         entry_index < dictionary->entry_count;
         entry_index++) {
        free_dictionary_entry(&dictionary->entries[entry_index]);
    }

    free(dictionary->entries);
    free(dictionary);
}

Dictionary *group_key_value_pairs(const KeyValuePair *pairs,
                                  size_t pair_count)
{
    Dictionary *dictionary;
    size_t pair_index;

    if (pairs == NULL && pair_count != 0) {
        return NULL;
    }

    dictionary = calloc(1, sizeof(*dictionary));
    if (dictionary == NULL) {
        return NULL;
    }

    for (pair_index = 0; pair_index < pair_count; pair_index++) {
        const KeyValuePair *pair = &pairs[pair_index];
        DictionaryEntry new_entry = {0};
        size_t entry_index;

        if (pair->key == NULL || pair->value == NULL) {
            free_dictionary(dictionary);
            return NULL;
        }

        for (entry_index = 0;
             entry_index < dictionary->entry_count;
             entry_index++) {
            const DictionaryEntry *entry =
                &dictionary->entries[entry_index];

            if (byte_strings_equal(entry->key,
                                   entry->key_length,
                                   pair->key,
                                   pair->key_length)) {
                break;
            }
        }

        if (entry_index < dictionary->entry_count) {
            if (!append_value(&dictionary->entries[entry_index],
                              pair->value,
                              pair->value_length)) {
                free_dictionary(dictionary);
                return NULL;
            }

            continue;
        }

        new_entry.key = duplicate_bytes(pair->key, pair->key_length);
        if (new_entry.key == NULL) {
            free_dictionary(dictionary);
            return NULL;
        }

        new_entry.key_length = pair->key_length;

        if (!append_value(&new_entry,
                          pair->value,
                          pair->value_length)) {
            free_dictionary_entry(&new_entry);
            free_dictionary(dictionary);
            return NULL;
        }

        if (dictionary->entry_count == SIZE_MAX) {
            free_dictionary_entry(&new_entry);
            free_dictionary(dictionary);
            return NULL;
        }

        if (dictionary->entry_count == dictionary->entry_capacity) {
            DictionaryEntry *resized_entries;
            size_t new_capacity;

            resized_entries = grow_array(
                dictionary->entries,
                dictionary->entry_capacity,
                dictionary->entry_count + 1,
                sizeof(*dictionary->entries),
                &new_capacity
            );

            if (resized_entries == NULL) {
                free_dictionary_entry(&new_entry);
                free_dictionary(dictionary);
                return NULL;
            }

            dictionary->entries = resized_entries;
            dictionary->entry_capacity = new_capacity;
        }

        dictionary->entries[dictionary->entry_count] = new_entry;
        dictionary->entry_count++;
    }

    return dictionary;
}

static int write_bytes(const char *data, size_t length)
{
    if (length == 0) {
        return 1;
    }

    if (data == NULL) {
        return 0;
    }

    return fwrite(data, 1, length, stdout) == length;
}

static int print_dictionary(const Dictionary *dictionary)
{
    size_t entry_index;

    if (dictionary == NULL) {
        return 0;
    }

    for (entry_index = 0;
         entry_index < dictionary->entry_count;
         entry_index++) {
        const DictionaryEntry *entry =
            &dictionary->entries[entry_index];
        size_t value_index;

        if (!write_bytes(entry->key, entry->key_length) ||
            fputs(": [", stdout) == EOF) {
            return 0;
        }

        for (value_index = 0;
             value_index < entry->value_count;
             value_index++) {
            const DictionaryValue *value =
                &entry->values[value_index];

            if (value_index != 0 && fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (!write_bytes(value->data, value->length)) {
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
        {
            "fruit",
            sizeof("fruit") - 1,
            "apple",
            sizeof("apple") - 1
        },
        {
            "color",
            sizeof("color") - 1,
            "blue",
            sizeof("blue") - 1
        },
        {
            "fruit",
            sizeof("fruit") - 1,
            "banana",
            sizeof("banana") - 1
        },
        {
            "animal",
            sizeof("animal") - 1,
            "cat",
            sizeof("cat") - 1
        },
        {
            "color",
            sizeof("color") - 1,
            "green",
            sizeof("green") - 1
        },
        {
            "fruit",
            sizeof("fruit") - 1,
            "orange",
            sizeof("orange") - 1
        }
    };
    Dictionary *dictionary;
    int status = EXIT_SUCCESS;

    dictionary = group_key_value_pairs(
        pairs,
        sizeof(pairs) / sizeof(pairs[0])
    );

    if (dictionary == NULL) {
        fputs("Failed to group key-value pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_dictionary(dictionary)) {
        status = EXIT_FAILURE;
    }

    free_dictionary(dictionary);
    return status;
}