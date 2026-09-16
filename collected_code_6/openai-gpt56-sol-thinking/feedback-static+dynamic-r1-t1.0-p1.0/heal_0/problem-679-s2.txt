#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DICTIONARY_OK,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_OUT_OF_RANGE,
    DICTIONARY_OUT_OF_MEMORY
} DictionaryStatus;

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
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

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary != NULL) {
        dictionary->entries = NULL;
        dictionary->size = 0;
        dictionary->capacity = 0;
    }
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
    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
}

static DictionaryStatus dictionary_reserve(Dictionary *dictionary)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary->size < dictionary->capacity) {
        return DICTIONARY_OK;
    }

    if (dictionary->capacity == 0) {
        new_capacity = 4;
    } else {
        if (dictionary->capacity > SIZE_MAX / 2) {
            return DICTIONARY_OUT_OF_MEMORY;
        }
        new_capacity = dictionary->capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*new_entries)
    );

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
    const char *value
)
{
    size_t index;
    char *key_copy;
    char *value_copy;
    DictionaryStatus status;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (index = 0; index < dictionary->size; ++index) {
        if (strcmp(dictionary->entries[index].key, key) == 0) {
            value_copy = duplicate_string(value);
            if (value_copy == NULL) {
                return DICTIONARY_OUT_OF_MEMORY;
            }

            free(dictionary->entries[index].value);
            dictionary->entries[index].value = value_copy;
            return DICTIONARY_OK;
        }
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return DICTIONARY_OUT_OF_MEMORY;
    }

    status = dictionary_reserve(dictionary);
    if (status != DICTIONARY_OK) {
        free(key_copy);
        free(value_copy);
        return status;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value_copy;
    ++dictionary->size;

    return DICTIONARY_OK;
}

static DictionaryStatus dictionary_key_at(
    const Dictionary *dictionary,
    size_t index,
    const char **key
)
{
    if (dictionary == NULL || key == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *key = NULL;

    if (index >= dictionary->size) {
        return DICTIONARY_OUT_OF_RANGE;
    }

    *key = dictionary->entries[index].key;
    return DICTIONARY_OK;
}

int main(void)
{
    Dictionary dictionary;
    DictionaryStatus status;
    const char *key;
    size_t index;

    dictionary_init(&dictionary);

    status = dictionary_set(&dictionary, "name", "Alice");
    if (status != DICTIONARY_OK) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    status = dictionary_set(&dictionary, "age", "30");
    if (status != DICTIONARY_OK) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    status = dictionary_set(&dictionary, "city", "London");
    if (status != DICTIONARY_OK) {
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    for (index = 0; index < dictionary.size; ++index) {
        status = dictionary_key_at(&dictionary, index, &key);
        if (status != DICTIONARY_OK) {
            dictionary_destroy(&dictionary);
            return EXIT_FAILURE;
        }

        if (printf("%zu: %s\n", index, key) < 0) {
            dictionary_destroy(&dictionary);
            return EXIT_FAILURE;
        }
    }

    dictionary_destroy(&dictionary);
    return EXIT_SUCCESS;
}