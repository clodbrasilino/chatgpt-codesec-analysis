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

static char *duplicate_string(const char *source, size_t length)
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
        if (source[index] == '\0') {
            free(copy);
            return NULL;
        }
        copy[index] = source[index];
    }

    copy[length] = '\0';
    return copy;
}

static int strings_equal(const char *left, size_t left_length,
                         const char *right, size_t right_length)
{
    size_t index;

    if (left == NULL || right == NULL || left_length != right_length) {
        return 0;
    }

    for (index = 0; index < left_length; index++) {
        if (left[index] != right[index]) {
            return 0;
        }
    }

    return 1;
}

static int reserve_array(void **array, size_t *capacity,
                         size_t minimum_capacity, size_t element_size)
{
    size_t maximum_capacity;
    size_t new_capacity;
    void *resized_array;

    if (array == NULL || capacity == NULL || element_size == 0) {
        return 0;
    }

    maximum_capacity = SIZE_MAX / element_size;

    if (*capacity > maximum_capacity ||
        minimum_capacity > maximum_capacity) {
        return 0;
    }

    if (minimum_capacity <= *capacity) {
        return minimum_capacity == 0 || *array != NULL;
    }

    new_capacity = *capacity;
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

    resized_array = realloc(*array, new_capacity * element_size);
    if (resized_array == NULL) {
        return 0;
    }

    *array = resized_array;
    *capacity = new_capacity;
    return 1;
}

static void free_dictionary_entry(DictionaryEntry *entry)
{
    size_t value_index;

    if (entry == NULL) {
        return;
    }

    free(entry->key);

    for (value_index = 0; value_index < entry->value_count; value_index++) {
        free(entry->values[value_index]);
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
    void *values;

    if (entry == NULL || value == NULL ||
        entry->value_count == SIZE_MAX) {
        return 0;
    }

    value_copy = duplicate_string(value, value_length);
    if (value_copy == NULL) {
        return 0;
    }

    values = entry->values;
    if (!reserve_array(&values,
                       &entry->value_capacity,
                       entry->value_count + 1,
                       sizeof(*entry->values))) {
        free(value_copy);
        return 0;
    }

    entry->values = values;
    entry->values[entry->value_count] = value_copy;
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
        void *entries;

        if (pair->key == NULL || pair->value == NULL) {
            free_dictionary(dictionary);
            return NULL;
        }

        for (entry_index = 0;
             entry_index < dictionary->entry_count;
             entry_index++) {
            /* Possible weaknesses found:
             *  Variable 'entry' can be declared as pointer to const [constVariablePointer]
             */
            DictionaryEntry *entry = &dictionary->entries[entry_index];

            if (strings_equal(entry->key,
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

        new_entry.key = duplicate_string(pair->key, pair->key_length);
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

        entries = dictionary->entries;
        if (!reserve_array(&entries,
                           &dictionary->entry_capacity,
                           dictionary->entry_count + 1,
                           sizeof(*dictionary->entries))) {
            free_dictionary_entry(&new_entry);
            free_dictionary(dictionary);
            return NULL;
        }

        dictionary->entries = entries;
        dictionary->entries[dictionary->entry_count] = new_entry;
        dictionary->entry_count++;
    }

    return dictionary;
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

        if (fputs(entry->key, stdout) == EOF ||
            fputs(": [", stdout) == EOF) {
            return 0;
        }

        for (value_index = 0;
             value_index < entry->value_count;
             value_index++) {
            if (value_index != 0 &&
                fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (fputs(entry->values[value_index], stdout) == EOF) {
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
        {"fruit", 5, "apple", 5},
        {"color", 5, "blue", 4},
        {"fruit", 5, "banana", 6},
        {"animal", 6, "cat", 3},
        {"color", 5, "green", 5},
        {"fruit", 5, "orange", 6}
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