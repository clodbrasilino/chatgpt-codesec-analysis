#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_data(const char *source, size_t length)
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

static bool data_equal(
    const char *first,
    size_t first_length,
    const char *second,
    size_t second_length
)
{
    size_t index;

    if (first_length != second_length) {
        return false;
    }

    for (index = 0; index < first_length; ++index) {
        if (first[index] != second[index]) {
            return false;
        }
    }

    return true;
}

static Dictionary *dictionary_create(void)
{
    return calloc(1, sizeof(Dictionary));
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    free(dictionary);
}

static bool dictionary_reserve(
    Dictionary *dictionary,
    size_t minimum_capacity
)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return false;
    }

    if (minimum_capacity <= dictionary->capacity) {
        return true;
    }

    new_capacity = dictionary->capacity == 0
        ? 8
        : dictionary->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = minimum_capacity;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return false;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*new_entries)
    );

    if (new_entries == NULL) {
        return false;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;

    return true;
}

static bool dictionary_put(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    const char *value,
    size_t value_length
)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return false;
    }

    if (key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return false;
    }

    for (index = 0; index < dictionary->size; ++index) {
        DictionaryEntry *entry = &dictionary->entries[index];

        if (data_equal(
                entry->key,
                entry->key_length,
                key,
                key_length)) {
            new_value = duplicate_data(value, value_length);
            if (new_value == NULL) {
                return false;
            }

            free(entry->value);
            entry->value = new_value;
            entry->value_length = value_length;
            return true;
        }
    }

    if (dictionary->size == SIZE_MAX) {
        return false;
    }

    new_key = duplicate_data(key, key_length);
    if (new_key == NULL) {
        return false;
    }

    new_value = duplicate_data(value, value_length);
    if (new_value == NULL) {
        free(new_key);
        return false;
    }

    if (!dictionary_reserve(dictionary, dictionary->size + 1)) {
        free(new_key);
        free(new_value);
        return false;
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = new_value;
    dictionary->entries[dictionary->size].value_length = value_length;
    ++dictionary->size;

    return true;
}

static Dictionary *dictionary_merge(
    const Dictionary *first,
    const Dictionary *second
)
{
    Dictionary *merged;
    size_t index;

    if (first == NULL || second == NULL) {
        return NULL;
    }

    merged = dictionary_create();
    if (merged == NULL) {
        return NULL;
    }

    for (index = 0; index < first->size; ++index) {
        const DictionaryEntry *entry = &first->entries[index];

        if (!dictionary_put(
                merged,
                entry->key,
                entry->key_length,
                entry->value,
                entry->value_length)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    for (index = 0; index < second->size; ++index) {
        const DictionaryEntry *entry = &second->entries[index];

        if (!dictionary_put(
                merged,
                entry->key,
                entry->key_length,
                entry->value,
                entry->value_length)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    return merged;
}

static bool write_data(const char *data, size_t length)
{
    if (length == 0) {
        return true;
    }

    return fwrite(data, 1, length, stdout) == length;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return false;
    }

    for (index = 0; index < dictionary->size; ++index) {
        const DictionaryEntry *entry = &dictionary->entries[index];

        if (!write_data(entry->key, entry->key_length) ||
            fputc('=', stdout) == EOF ||
            !write_data(entry->value, entry->value_length) ||
            fputc('\n', stdout) == EOF) {
            return false;
        }
    }

    return fflush(stdout) == 0;
}

int main(void)
{
    Dictionary *first = NULL;
    Dictionary *second = NULL;
    Dictionary *merged = NULL;
    int result = EXIT_FAILURE;

    first = dictionary_create();
    second = dictionary_create();

    if (first == NULL || second == NULL) {
        goto cleanup;
    }

    if (!dictionary_put(
            first,
            "name",
            sizeof("name") - 1,
            "Alice",
            sizeof("Alice") - 1) ||
        !dictionary_put(
            first,
            "city",
            sizeof("city") - 1,
            "Paris",
            sizeof("Paris") - 1) ||
        !dictionary_put(
            second,
            "city",
            sizeof("city") - 1,
            "Berlin",
            sizeof("Berlin") - 1) ||
        !dictionary_put(
            second,
            "role",
            sizeof("role") - 1,
            "Engineer",
            sizeof("Engineer") - 1)) {
        goto cleanup;
    }

    merged = dictionary_merge(first, second);
    if (merged == NULL) {
        goto cleanup;
    }

    if (!dictionary_print(merged)) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(merged);
    dictionary_destroy(second);
    dictionary_destroy(first);

    return result;
}