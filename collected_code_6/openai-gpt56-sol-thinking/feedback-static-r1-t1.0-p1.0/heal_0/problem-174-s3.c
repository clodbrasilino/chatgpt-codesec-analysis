#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

static char *duplicate_string(const char *source)
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

static int reserve_array(void **array, size_t *capacity,
                         size_t minimum_capacity, size_t element_size)
{
    size_t maximum_capacity;
    size_t new_capacity;
    void *resized_array;

    if (array == NULL || capacity == NULL || element_size == 0) {
        return 0;
    }

    if (minimum_capacity <= *capacity) {
        return 1;
    }

    maximum_capacity = SIZE_MAX / element_size;
    if (minimum_capacity > maximum_capacity) {
        return 0;
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

static int append_value(DictionaryEntry *entry, const char *value)
{
    char *value_copy;

    if (entry == NULL || value == NULL || entry->value_count == SIZE_MAX) {
        return 0;
    }

    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        return 0;
    }

    if (!reserve_array((void **)&entry->values,
                       &entry->value_capacity,
                       entry->value_count + 1,
                       sizeof(*entry->values))) {
        free(value_copy);
        return 0;
    }

    entry->values[entry->value_count] = value_copy;
    entry->value_count++;
    return 1;
}

void free_dictionary(Dictionary *dictionary)
{
    size_t entry_index;
    size_t value_index;

    if (dictionary == NULL) {
        return;
    }

    for (entry_index = 0; entry_index < dictionary->entry_count; entry_index++) {
        DictionaryEntry *entry = &dictionary->entries[entry_index];

        free(entry->key);
        for (value_index = 0; value_index < entry->value_count; value_index++) {
            free(entry->values[value_index]);
        }
        free(entry->values);
    }

    free(dictionary->entries);
    free(dictionary);
}

Dictionary *group_key_value_pairs(const KeyValuePair *pairs, size_t pair_count)
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
        size_t entry_index;
        DictionaryEntry new_entry = {0};

        if (pairs[pair_index].key == NULL || pairs[pair_index].value == NULL) {
            free_dictionary(dictionary);
            return NULL;
        }

        for (entry_index = 0;
             entry_index < dictionary->entry_count;
             entry_index++) {
            if (strcmp(dictionary->entries[entry_index].key,
                       pairs[pair_index].key) == 0) {
                break;
            }
        }

        if (entry_index < dictionary->entry_count) {
            if (!append_value(&dictionary->entries[entry_index],
                              pairs[pair_index].value)) {
                free_dictionary(dictionary);
                return NULL;
            }
            continue;
        }

        new_entry.key = duplicate_string(pairs[pair_index].key);
        if (new_entry.key == NULL ||
            !append_value(&new_entry, pairs[pair_index].value)) {
            free(new_entry.key);
            free(new_entry.values);
            free_dictionary(dictionary);
            return NULL;
        }

        if (dictionary->entry_count == SIZE_MAX ||
            !reserve_array((void **)&dictionary->entries,
                           &dictionary->entry_capacity,
                           dictionary->entry_count + 1,
                           sizeof(*dictionary->entries))) {
            free(new_entry.key);
            free(new_entry.values[0]);
            free(new_entry.values);
            free_dictionary(dictionary);
            return NULL;
        }

        dictionary->entries[dictionary->entry_count] = new_entry;
        dictionary->entry_count++;
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

    for (entry_index = 0; entry_index < dictionary->entry_count; entry_index++) {
        const DictionaryEntry *entry = &dictionary->entries[entry_index];

        if (printf("%s: [", entry->key) < 0) {
            return 0;
        }

        for (value_index = 0; value_index < entry->value_count; value_index++) {
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