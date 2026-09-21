#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary_init(dictionary);
}

static bool duplicate_string(const char *source, size_t length, char **copy)
{
    char *result;
    size_t i;

    if (source == NULL || copy == NULL || length == SIZE_MAX) {
        return false;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return false;
    }

    for (i = 0; i < length; ++i) {
        if (source[i] == '\0') {
            free(result);
            return false;
        }

        result[i] = source[i];
    }

    result[length] = '\0';
    *copy = result;
    return true;
}

static bool dictionary_reserve(Dictionary *dictionary,
                               size_t required_capacity)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return false;
    }

    if (required_capacity <= dictionary->capacity) {
        return true;
    }

    new_capacity = dictionary->capacity == 0 ? 8 : dictionary->capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required_capacity;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return false;
    }

    new_entries = realloc(dictionary->entries,
                          new_capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return false;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return true;
}

static bool dictionary_add(Dictionary *dictionary,
                           const char *key,
                           size_t key_length,
                           const char *value,
                           size_t value_length)
{
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL ||
        dictionary->size == SIZE_MAX ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0 && dictionary->entries == NULL)) {
        return false;
    }

    if (!duplicate_string(key, key_length, &key_copy)) {
        return false;
    }

    if (!duplicate_string(value, value_length, &value_copy)) {
        free(key_copy);
        return false;
    }

    if (!dictionary_reserve(dictionary, dictionary->size + 1)) {
        free(key_copy);
        free(value_copy);
        return false;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value_copy;
    ++dictionary->size;

    return true;
}

bool dictionary_drop_empty_items(Dictionary *dictionary, size_t *removed)
{
    size_t original_size;
    size_t read_index;
    size_t write_index;

    if (dictionary == NULL || removed == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0 && dictionary->entries == NULL)) {
        return false;
    }

    original_size = dictionary->size;
    write_index = 0;

    for (read_index = 0; read_index < original_size; ++read_index) {
        DictionaryEntry *entry = &dictionary->entries[read_index];
        bool is_empty = entry->key == NULL ||
                        entry->value == NULL ||
                        entry->key[0] == '\0' ||
                        entry->value[0] == '\0';

        if (is_empty) {
            free(entry->key);
            free(entry->value);
            entry->key = NULL;
            entry->value = NULL;
            continue;
        }

        if (write_index != read_index) {
            dictionary->entries[write_index] = *entry;
            entry->key = NULL;
            entry->value = NULL;
        }

        ++write_index;
    }

    dictionary->size = write_index;
    *removed = original_size - write_index;

    return true;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0 && dictionary->entries == NULL)) {
        return false;
    }

    for (i = 0; i < dictionary->size; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key == NULL || entry->value == NULL) {
            return false;
        }

        if (printf("%s: %s\n", entry->key, entry->value) < 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    Dictionary dictionary;
    size_t removed;

    dictionary_init(&dictionary);

    if (!dictionary_add(&dictionary,
                        "name", sizeof("name") - 1,
                        "Ada", sizeof("Ada") - 1) ||
        !dictionary_add(&dictionary,
                        "email", sizeof("email") - 1,
                        "", sizeof("") - 1) ||
        !dictionary_add(&dictionary,
                        "", sizeof("") - 1,
                        "invalid", sizeof("invalid") - 1) ||
        !dictionary_add(&dictionary,
                        "language", sizeof("language") - 1,
                        "C", sizeof("C") - 1)) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    if (!dictionary_drop_empty_items(&dictionary, &removed)) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    if (printf("Removed: %zu\n", removed) < 0 ||
        !dictionary_print(&dictionary)) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    dictionary_destroy(&dictionary);
    return EXIT_SUCCESS;
}