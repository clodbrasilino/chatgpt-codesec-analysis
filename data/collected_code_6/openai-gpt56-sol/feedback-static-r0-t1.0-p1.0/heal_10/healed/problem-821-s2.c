#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} Entry;

typedef struct {
    Entry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static int string_length(const char *string, size_t *length)
{
    const char *current;
    size_t result = 0U;

    if (string == NULL || length == NULL) {
        return 0;
    }

    current = string;
    while (*current != '\0') {
        if (result == SIZE_MAX) {
            return 0;
        }

        ++current;
        ++result;
    }

    *length = result;
    return 1;
}

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static size_t dictionary_find(const Dictionary *dictionary,
                              const char *key,
                              size_t key_length)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key != NULL &&
            entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return index;
        }
    }

    return SIZE_MAX;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;

    if (dictionary == NULL) {
        return 0;
    }

    if (capacity <= dictionary->capacity) {
        return 1;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return 0;
    }

    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*dictionary->entries));
    if (new_entries == NULL) {
        return 0;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 1;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          size_t key_length,
                          const char *value,
                          size_t value_length)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return 0;
    }

    index = dictionary_find(dictionary, key, key_length);

    new_value = duplicate_string(value, value_length);
    if (new_value == NULL) {
        return 0;
    }

    if (index != SIZE_MAX) {
        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        dictionary->entries[index].value_length = value_length;
        return 1;
    }

    new_key = duplicate_string(key, key_length);
    if (new_key == NULL) {
        free(new_value);
        return 0;
    }

    if (dictionary->count == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                free(new_key);
                free(new_value);
                return 0;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (!dictionary_reserve(dictionary, new_capacity)) {
            free(new_key);
            free(new_value);
            return 0;
        }
    }

    dictionary->entries[dictionary->count].key = new_key;
    dictionary->entries[dictionary->count].key_length = key_length;
    dictionary->entries[dictionary->count].value = new_value;
    dictionary->entries[dictionary->count].value_length = value_length;
    ++dictionary->count;

    return 1;
}

static int dictionary_set_cstr(Dictionary *dictionary,
                               const char *key,
                               const char *value)
{
    size_t key_length;
    size_t value_length;

    if (!string_length(key, &key_length) ||
        !string_length(value, &value_length)) {
        return 0;
    }

    return dictionary_set(dictionary, key, key_length,
                          value, value_length);
}

static int dictionary_merge(const Dictionary *first,
                            const Dictionary *second,
                            Dictionary *result)
{
    size_t index;
    Dictionary merged = { NULL, 0U, 0U };

    if (first == NULL || second == NULL || result == NULL ||
        first == result || second == result) {
        return 0;
    }

    if (first->count > SIZE_MAX - second->count) {
        return 0;
    }

    if (!dictionary_reserve(&merged, first->count + second->count)) {
        return 0;
    }

    for (index = 0U; index < first->count; ++index) {
        const Entry *entry = &first->entries[index];

        if (entry->key == NULL || entry->value == NULL ||
            !dictionary_set(&merged,
                            entry->key,
                            entry->key_length,
                            entry->value,
                            entry->value_length)) {
            dictionary_destroy(&merged);
            return 0;
        }
    }

    for (index = 0U; index < second->count; ++index) {
        const Entry *entry = &second->entries[index];

        if (entry->key == NULL || entry->value == NULL ||
            !dictionary_set(&merged,
                            entry->key,
                            entry->key_length,
                            entry->value,
                            entry->value_length)) {
            dictionary_destroy(&merged);
            return 0;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return 1;
}

static int write_all(const char *data, size_t length)
{
    while (length > 0U) {
        size_t written = fwrite(data, 1U, length, stdout);

        if (written == 0U) {
            return 0;
        }

        data += written;
        length -= written;
    }

    return 1;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL || fputc('{', stdout) == EOF) {
        return 0;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key == NULL || entry->value == NULL) {
            return 0;
        }

        if (index != 0U && !write_all(", ", 2U)) {
            return 0;
        }

        if (!write_all("\"", 1U) ||
            !write_all(entry->key, entry->key_length) ||
            !write_all("\": \"", 4U) ||
            !write_all(entry->value, entry->value_length) ||
            !write_all("\"", 1U)) {
            return 0;
        }
    }

    return write_all("}\n", 2U);
}

int main(void)
{
    Dictionary first = { NULL, 0U, 0U };
    Dictionary second = { NULL, 0U, 0U };
    Dictionary merged = { NULL, 0U, 0U };
    int status = EXIT_FAILURE;

    if (!dictionary_set_cstr(&first, "name", "Alice") ||
        !dictionary_set_cstr(&first, "role", "developer") ||
        !dictionary_set_cstr(&second, "role", "lead developer") ||
        !dictionary_set_cstr(&second, "location", "London")) {
        goto cleanup;
    }

    if (!dictionary_merge(&first, &second, &merged)) {
        goto cleanup;
    }

    if (!dictionary_print(&merged)) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}