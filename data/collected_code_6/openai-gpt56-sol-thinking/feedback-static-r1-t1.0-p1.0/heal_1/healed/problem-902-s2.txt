#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    size_t key_length;
    int64_t value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

typedef enum {
    DICTIONARY_OK,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_OUT_OF_MEMORY,
    DICTIONARY_OVERFLOW
} DictionaryStatus;

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary != NULL) {
        dictionary->entries = NULL;
        dictionary->count = 0;
        dictionary->capacity = 0;
    }
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->count; ++i) {
        free(dictionary->entries[i].key);
    }

    free(dictionary->entries);
    dictionary_init(dictionary);
}

static DictionaryStatus copy_key(
    const char *source,
    size_t length,
    char **destination)
{
    char *copy;
    size_t i;

    if (source == NULL || destination == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return DICTIONARY_OVERFLOW;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    *destination = copy;

    return DICTIONARY_OK;
}

static bool keys_equal(
    const DictionaryEntry *entry,
    const char *key,
    size_t key_length)
{
    size_t i;

    if (entry == NULL || key == NULL || entry->key_length != key_length) {
        return false;
    }

    for (i = 0; i < key_length; ++i) {
        if (entry->key[i] != key[i]) {
            return false;
        }
    }

    return true;
}

static bool dictionary_find(
    const Dictionary *dictionary,
    const char *key,
    size_t key_length,
    size_t *index)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (keys_equal(&dictionary->entries[i], key, key_length)) {
            if (index != NULL) {
                *index = i;
            }
            return true;
        }
    }

    return false;
}

static DictionaryStatus dictionary_reserve(
    Dictionary *dictionary,
    size_t required_capacity)
{
    size_t maximum_capacity;
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (required_capacity <= dictionary->capacity) {
        return DICTIONARY_OK;
    }

    maximum_capacity = SIZE_MAX / sizeof(*dictionary->entries);
    if (required_capacity > maximum_capacity) {
        return DICTIONARY_OVERFLOW;
    }

    if (dictionary->capacity == 0) {
        new_capacity = maximum_capacity < 8 ? maximum_capacity : 8;
    } else {
        new_capacity = dictionary->capacity;
    }

    while (new_capacity < required_capacity) {
        if (new_capacity > maximum_capacity / 2) {
            new_capacity = maximum_capacity;
        } else {
            new_capacity *= 2;
        }
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*dictionary->entries));

    if (new_entries == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;

    return DICTIONARY_OK;
}

static DictionaryStatus dictionary_set(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    int64_t value)
{
    size_t index;
    char *key_copy;
    DictionaryStatus status;

    if (dictionary == NULL || key == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary_find(dictionary, key, key_length, &index)) {
        dictionary->entries[index].value = value;
        return DICTIONARY_OK;
    }

    if (dictionary->count == SIZE_MAX) {
        return DICTIONARY_OVERFLOW;
    }

    status = dictionary_reserve(dictionary, dictionary->count + 1);
    if (status != DICTIONARY_OK) {
        return status;
    }

    status = copy_key(key, key_length, &key_copy);
    if (status != DICTIONARY_OK) {
        return status;
    }

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].key_length = key_length;
    dictionary->entries[dictionary->count].value = value;
    ++dictionary->count;

    return DICTIONARY_OK;
}

static DictionaryStatus dictionary_add(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    int64_t value)
{
    size_t index;
    int64_t current;

    if (dictionary == NULL || key == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (!dictionary_find(dictionary, key, key_length, &index)) {
        return dictionary_set(dictionary, key, key_length, value);
    }

    current = dictionary->entries[index].value;

    if ((value > 0 && current > INT64_MAX - value) ||
        (value < 0 && current < INT64_MIN - value)) {
        return DICTIONARY_OVERFLOW;
    }

    dictionary->entries[index].value = current + value;
    return DICTIONARY_OK;
}

DictionaryStatus dictionary_combine(
    const Dictionary *first,
    const Dictionary *second,
    Dictionary *result)
{
    Dictionary combined;
    DictionaryStatus status;
    size_t i;

    if (first == NULL || second == NULL || result == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    dictionary_init(&combined);

    for (i = 0; i < first->count; ++i) {
        status = dictionary_set(
            &combined,
            first->entries[i].key,
            first->entries[i].key_length,
            first->entries[i].value);

        if (status != DICTIONARY_OK) {
            dictionary_destroy(&combined);
            return status;
        }
    }

    for (i = 0; i < second->count; ++i) {
        status = dictionary_add(
            &combined,
            second->entries[i].key,
            second->entries[i].key_length,
            second->entries[i].value);

        if (status != DICTIONARY_OK) {
            dictionary_destroy(&combined);
            return status;
        }
    }

    dictionary_destroy(result);
    *result = combined;

    return DICTIONARY_OK;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary combined;
    DictionaryStatus status;
    size_t i;
    int exit_code = EXIT_FAILURE;

    dictionary_init(&first);
    dictionary_init(&second);
    dictionary_init(&combined);

    status = dictionary_set(
        &first, "apple", sizeof("apple") - 1, INT64_C(3));
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_set(
        &first, "banana", sizeof("banana") - 1, INT64_C(5));
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_set(
        &second, "banana", sizeof("banana") - 1, INT64_C(7));
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_set(
        &second, "cherry", sizeof("cherry") - 1, INT64_C(4));
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_combine(&first, &second, &combined);
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    for (i = 0; i < combined.count; ++i) {
        if (fwrite(
                combined.entries[i].key,
                1,
                combined.entries[i].key_length,
                stdout) != combined.entries[i].key_length) {
            goto cleanup;
        }

        if (printf(": %" PRId64 "\n", combined.entries[i].value) < 0) {
            goto cleanup;
        }
    }

    if (fflush(stdout) == EOF) {
        goto cleanup;
    }

    exit_code = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&combined);
    dictionary_destroy(&second);
    dictionary_destroy(&first);

    return exit_code;
}