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
    size_t count;
    size_t capacity;
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

    for (index = 0; index < length; ++index) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    return copy;
}

static bool strings_equal(
    const char *first,
    size_t first_length,
    const char *second,
    size_t second_length
)
{
    size_t index;

    if (first == NULL || second == NULL || first_length != second_length) {
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

    for (index = 0; index < dictionary->count; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    free(dictionary);
}

static bool dictionary_reserve(
    Dictionary *dictionary,
    size_t required_capacity
)
{
    size_t maximum_capacity;
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return false;
    }

    if (required_capacity <= dictionary->capacity) {
        return true;
    }

    maximum_capacity = SIZE_MAX / sizeof(*dictionary->entries);
    if (required_capacity > maximum_capacity) {
        return false;
    }

    if (dictionary->capacity == 0) {
        new_capacity = maximum_capacity < 4 ? maximum_capacity : 4;
    } else {
        new_capacity = dictionary->capacity;
    }

    while (new_capacity < required_capacity) {
        if (new_capacity > maximum_capacity / 2) {
            new_capacity = required_capacity;
            break;
        }

        new_capacity *= 2;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*dictionary->entries)
    );

    if (new_entries == NULL) {
        return false;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return true;
}

static bool dictionary_set(
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

    for (index = 0; index < dictionary->count; ++index) {
        if (strings_equal(
                dictionary->entries[index].key,
                dictionary->entries[index].key_length,
                key,
                key_length)) {
            new_value = duplicate_string(value, value_length);
            if (new_value == NULL) {
                return false;
            }

            free(dictionary->entries[index].value);
            dictionary->entries[index].value = new_value;
            dictionary->entries[index].value_length = value_length;
            return true;
        }
    }

    if (dictionary->count == SIZE_MAX) {
        return false;
    }

    if (!dictionary_reserve(dictionary, dictionary->count + 1)) {
        return false;
    }

    new_key = duplicate_string(key, key_length);
    if (new_key == NULL) {
        return false;
    }

    new_value = duplicate_string(value, value_length);
    if (new_value == NULL) {
        free(new_key);
        return false;
    }

    dictionary->entries[dictionary->count].key = new_key;
    dictionary->entries[dictionary->count].key_length = key_length;
    dictionary->entries[dictionary->count].value = new_value;
    dictionary->entries[dictionary->count].value_length = value_length;
    ++dictionary->count;

    return true;
}

static Dictionary *merge_dictionaries(
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

    for (index = 0; index < first->count; ++index) {
        if (!dictionary_set(
                merged,
                first->entries[index].key,
                first->entries[index].key_length,
                first->entries[index].value,
                first->entries[index].value_length)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    for (index = 0; index < second->count; ++index) {
        if (!dictionary_set(
                merged,
                second->entries[index].key,
                second->entries[index].key_length,
                second->entries[index].value,
                second->entries[index].value_length)) {
            dictionary_destroy(merged);
            return NULL;
        }
    }

    return merged;
}

static bool write_bytes(const char *data, size_t length)
{
    if (data == NULL) {
        return false;
    }

    return length == 0 || fwrite(data, 1, length, stdout) == length;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return false;
    }

    for (index = 0; index < dictionary->count; ++index) {
        if (!write_bytes(
                dictionary->entries[index].key,
                dictionary->entries[index].key_length) ||
            fputs(": ", stdout) == EOF ||
            !write_bytes(
                dictionary->entries[index].value,
                dictionary->entries[index].value_length) ||
            fputc('\n', stdout) == EOF) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    Dictionary *first;
    Dictionary *second;
    Dictionary *merged;
    int status;

    first = dictionary_create();
    second = dictionary_create();
    merged = NULL;
    status = EXIT_FAILURE;

    if (first == NULL || second == NULL) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (!dictionary_set(
            first, "name", sizeof("name") - 1,
            "Alice", sizeof("Alice") - 1) ||
        !dictionary_set(
            first, "city", sizeof("city") - 1,
            "London", sizeof("London") - 1) ||
        !dictionary_set(
            second, "city", sizeof("city") - 1,
            "Paris", sizeof("Paris") - 1) ||
        !dictionary_set(
            second, "country", sizeof("country") - 1,
            "France", sizeof("France") - 1)) {
        fputs("Failed to populate dictionaries.\n", stderr);
        goto cleanup;
    }

    merged = merge_dictionaries(first, second);
    if (merged == NULL) {
        fputs("Failed to merge dictionaries.\n", stderr);
        goto cleanup;
    }

    if (!dictionary_print(merged) || fflush(stdout) == EOF) {
        fputs("Failed to print dictionary.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(merged);
    dictionary_destroy(second);
    dictionary_destroy(first);
    return status;
}